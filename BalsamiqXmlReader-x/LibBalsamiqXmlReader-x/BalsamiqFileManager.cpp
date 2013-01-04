/*
 *  BalsamiqFileManager.cpp
 *  BalsamiqReaderWithCocos2dx
 *
 *  Created by 青宝 中 on 12-4-9.
 *  Copyright 2012年 __MyCompanyName__. All rights reserved.
 *
 */

#include "BalsamiqFileManager.h"
#include "BalsamiqReaderConfig.h"
#include "BalsamiqControlData.h"
#include <libxml/tree.h>
#include <libxml/xpath.h>
#include <libxml/xpathInternals.h>

#include <sys/stat.h>
#include <dirent.h>

using std::string;

USING_NS_CC;

#define MAX_PATH (1024)

string getLastPathComponent(string filePath)
{
    string::size_type lastPathIndex = filePath.rfind("/");
    if (lastPathIndex == string::npos)
    {
        return filePath;
    }
    else
    {
        return filePath.substr(lastPathIndex + 1);
    }
}

string getPathExtension(string filePath)
{
    string::size_type lastExtensionIndex = filePath.rfind(".");
    if (lastExtensionIndex == string::npos)
    {
        return filePath;
    }
    else
    {
        return filePath.substr(lastExtensionIndex + 1);
    }
}

xmlNodePtr getChildNode(xmlNodePtr node, xmlChar *childName)
{
    for (xmlNodePtr child = node->children;
         child != NULL;
         child = child->next)
    {
        if (xmlStrcmp(child->name, childName) == 0)
        {
            return child;
        }
    }
    
    return NULL;
}

using namespace cocos2d;

BalsamiqFileManager::BalsamiqFileManager():
allControlInfo(new FileNameAndControlDic())
{
//    loadAllControlInfo(BalsamiqReaderConfig::sharedBalsamiqReaderConfig()->getRootDir());
}

BalsamiqFileManager::~BalsamiqFileManager()
{
    CC_SAFE_RELEASE(allControlInfo);
}

BalsamiqFileManager *BalsamiqFileManager::sharedBalsamiqFileManager()
{
    static BalsamiqFileManager *mgr = NULL;
    if (mgr == NULL)
    {
        mgr = new BalsamiqFileManager();
    }
    
    return mgr;
}

CCArray *BalsamiqFileManager::getControlDataFromFileName(string bmmlFileName)
{
    return static_cast<CCArray *>(allControlInfo->objectForKey(bmmlFileName));
}

void BalsamiqFileManager::loadAllControlInfo(string rootDir)
{
    CCAssert(rootDir != "", "BalsamiqFileManager::loadFileFromRootDir param is NULL");
   
    NameToPathMap map;
    makeBmmlFileList(CCFileUtils::sharedFileUtils()->fullPathFromRelativePath(rootDir.c_str()), map);
    //printNameToPathMap(map);
    
    for (NameToPathMap::iterator iter = map.begin(); iter != map.end(); ++iter)
    {
        allControlInfo->setObject(this->parseFileControlInfo(iter->second),
                                  iter->first);
    }
}

CCArray *BalsamiqFileManager::parseFileControlInfo(string filePath)
{
    xmlDocPtr doc = xmlParseFile(filePath.c_str());
    xmlNodePtr controls = getChildNode(doc->children, BAD_CAST "controls");
    if (controls == NULL)
    {
        CCLog("BalsamiqFileManager::parseFileControlInfo can not find controls node");
        return NULL;
    }
    
    CCArray *array = CCArray::create();
    
    for (xmlNodePtr control = controls->children;
         control != NULL;
         control = control->next)
    {
        if (xmlStrcmp(control->name,BAD_CAST "control") == 0)
        {
            array->addObject(this->parseControlInfo(control));
        }
    }
    
    return array;
}

void BalsamiqFileManager::makeBmmlFileList(string dir, NameToPathMap &nameToPathMap)
{
	struct dirent *dp;
	DIR *dfd;
    
	if ((dfd = opendir(dir.c_str())) == NULL)
    {
		fprintf(stderr, "dirwalk: can't open %s\n", dir.c_str());
		return;
	}
    
	while ((dp = readdir(dfd)) != NULL)
    {
		if (strcmp(dp->d_name, ".") == 0
		    || strcmp(dp->d_name, "..") == 0)
        {
			continue;    /* skip self and parent */
        }
		else
        {
            string filePath = dir + "/" + dp->d_name;
            struct stat stbuf;
            
            if (stat(filePath.c_str(), &stbuf) == -1)
            {
                fprintf(stderr, "fsize: can't access %s\n", filePath.c_str());
                return;
            }
            
            if ((stbuf.st_mode & S_IFMT) == S_IFDIR)
            {
                this->makeBmmlFileList(filePath, nameToPathMap);
            }
            else
            {
                if (getPathExtension(filePath) == "bmml")
                {
                    if (nameToPathMap.find(getLastPathComponent(filePath)) != nameToPathMap.end())
                    {
                        CCLog("BalsamiqFileManager::makeBmmlFileList file name = %s is exist!",
                              getLastPathComponent(filePath).c_str());
                    }
                    
                    nameToPathMap[getLastPathComponent(filePath)] = filePath;
                }   
            }
		}
	}
	closedir(dfd);
}

void BalsamiqFileManager::printNameToPathMap(NameToPathMap &nameToPathMap) const
{
    printf("BalsamiqFileManager::printNameToPathMap start\n");
    
    for (NameToPathMap::iterator iter = nameToPathMap.begin(); iter != nameToPathMap.end(); ++iter)
    {
        printf("fileName = %s, filePath = %s\n", iter->first.c_str(), iter->second.c_str());
    }
    
    printf("BalsamiqFileManager::printNameToPathMap end\n");
}

BalsamiqControlData *BalsamiqFileManager::parseControlInfo(xmlNodePtr node)
{
    if (xmlStrcmp(node->name,BAD_CAST "control") != 0)
    {
        return NULL;
    }
    
    BalsamiqControlData *data = BalsamiqControlData::balsamiqControlData();
    
    // 1 保存属性
    for (xmlAttrPtr attribute = node->properties;
         attribute != NULL;
         attribute = attribute->next)
    {
        CCString *value = new CCString((char *)attribute->children->content);
        value->autorelease();
        
        data->getAttributeDic()->setObject(value, (char *)attribute->name);
    }
    
    // 2 保持属于properties节点下的属性
    xmlNodePtr propertiesNode = getChildNode(node, BAD_CAST "controlProperties");
    if (propertiesNode != NULL)
    {
        for (xmlNodePtr property = propertiesNode->children;
             property != NULL;
             property = property->next)
        {
            if (property->type == XML_ELEMENT_NODE)
            {
                
                CCString *value = new CCString((char *)property->children->content);
                value->autorelease();
                
                data->getPropertyDic()->setObject(value, (char *)property->name);
            }
        }
    }
    
    //data->printData();
    
    return data;
}