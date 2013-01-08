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
#include "BalsamiqFileParser.h"

#include <libxml/tree.h>
#include <libxml/xpath.h>
#include <libxml/xpathInternals.h>

#include <sys/stat.h>
#include <dirent.h>

using std::string;

USING_NS_CC;

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
    
//    for (NameToPathMap::iterator iter = map.begin(); iter != map.end(); ++iter)
//    {
//        allControlInfo->setObject(BalsamiqFileParser::sharedBalsamiqFileParser()->parseFileControlInfo(iter->second),
//                                  iter->first);
//    }
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
