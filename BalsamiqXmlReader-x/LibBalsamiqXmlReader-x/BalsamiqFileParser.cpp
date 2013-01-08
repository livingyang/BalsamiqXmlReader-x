/*
 *  BalsamiqFileParser.cpp
 *  BalsamiqXmlReader-x
 *
 *  Created by 中 青宝 on 13-1-4.
 *  Copyright 2013年 __MyCompanyName__. All rights reserved.
 *
 */

#include "BalsamiqFileParser.h"
#include "BalsamiqControlData.h"
#include "BalsamiqBmmlData.h"

USING_NS_CC;
using std::string;

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

BalsamiqFileParser *BalsamiqFileParser::sharedBalsamiqFileParser()
{
    static BalsamiqFileParser *parser = NULL;
    if (parser == NULL)
    {
        parser = new BalsamiqFileParser();
    }
    
    return parser;
}

BalsamiqFileParser::BalsamiqFileParser()
{
}

BalsamiqFileParser::~BalsamiqFileParser()
{
}

CCArray *BalsamiqFileParser::parseFileControlInfo(string filePath)
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

BalsamiqControlData *BalsamiqFileParser::parseControlInfo(xmlNodePtr node)
{
    if (xmlStrcmp(node->name,BAD_CAST "control") != 0)
    {
        return NULL;
    }
    
    BalsamiqControlData *data = BalsamiqControlData::create();
    
    // 1 保存属性
    for (xmlAttrPtr attribute = node->properties;
         attribute != NULL;
         attribute = attribute->next)
    {
        CCString *value = CCString::create((attribute->children == NULL)
                                           ? ""
                                           : (char *)attribute->children->content);
        
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
                CCString *value = CCString::create((property->children == NULL)
                                                   ? ""
                                                   : (char *)property->children->content);
                
                data->getPropertyDic()->setObject(value, (char *)property->name);
            }
        }
    }
    
    return data;
}

BalsamiqBmmlData *BalsamiqFileParser::parseBmmlFile(std::string bmmlFilePath)
{
    BalsamiqBmmlData *data = BalsamiqBmmlData::create();
    
    data->setBmmlFilePath(bmmlFilePath);
    data->setControlDataArray(parseFileControlInfo(bmmlFilePath));
    
    return data;
}
