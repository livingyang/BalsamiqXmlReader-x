/*
 *  BalsamiqBmmlData.cpp
 *  BalsamiqXmlReader-x
 *
 *  Created by 中 青宝 on 13-1-5.
 *  Copyright 2013年 __MyCompanyName__. All rights reserved.
 *
 */

#include "BalsamiqBmmlData.h"

USING_NS_CC;
using std::string;

BalsamiqBmmlData::BalsamiqBmmlData():
controlDataArray(new CCArray())
{
}

BalsamiqBmmlData::~BalsamiqBmmlData()
{
    setControlDataArray(NULL);
}

void BalsamiqBmmlData::setBmmlFilePath(const std::string &var)
{
    bmmlFilePath = var;
    
    string::size_type lastPathIndex = bmmlFilePath.rfind("/");
    if (lastPathIndex == string::npos)
    {
        bmmlFileDic = "";
        bmmlFileName = bmmlFilePath;
    }
    else
    {
        bmmlFileDic = bmmlFilePath.substr(0, lastPathIndex + 1);
        bmmlFileName = bmmlFilePath.substr(lastPathIndex + 1);
    }
}

std::string BalsamiqBmmlData::getBmmlFilePath()
{
    return bmmlFilePath;
}

BalsamiqBmmlData *BalsamiqBmmlData::create()
{
    return static_cast<BalsamiqBmmlData *>((new BalsamiqBmmlData())->autorelease());
}

std::string BalsamiqBmmlData::description()
{
    std::stringstream ss;
    
    ss << "{\n";
    
    ss << "file path = " << getBmmlFilePath().c_str() << "\n\n";
    
    ss << "control array = [\n";
    
    for (int i = 0; i < getControlDataArray()->count(); ++i)
    {
        BalsamiqControlData *controlData = static_cast<BalsamiqControlData *>(getControlDataArray()->objectAtIndex(i));
        
        
        ss << controlData->description().c_str();
        
        ss << "\n";
    }
    
    ss << "]\n";
    
    ss << "}\n";
    
    return ss.str();
}

#pragma mark -
#pragma mark BalsamiqControlData

BalsamiqControlData::BalsamiqControlData():
attributeDic(new CCDictionary()),
propertyDic(new CCDictionary())
{
}

BalsamiqControlData::~BalsamiqControlData()
{
    setAttributeDic(NULL);
    setPropertyDic(NULL);
}

BalsamiqControlData *BalsamiqControlData::create()
{
    return static_cast<BalsamiqControlData *>((new BalsamiqControlData())->autorelease());
}

void appendDictionaryDataToStream(CCDictionary *dic, std::stringstream &ss)
{
    CCDictElement* pElement = NULL;
    CCDICT_FOREACH(dic, pElement)
    {
        CCString *value = (CCString *)pElement->getObject();
        
        ss << "\t\t" << pElement->getStrKey() << " = " << value->getCString() << ",\n";
    }
}

std::string BalsamiqControlData::description()
{
    std::stringstream ss;
    
    ss << "{\n";
    ss <<"\tattribute = {\n";
    appendDictionaryDataToStream(getAttributeDic(), ss);
    ss << "\t},\n";
    
    ss << "\tproperties = {\n";
    appendDictionaryDataToStream(getPropertyDic(), ss);
    ss << "\t}\n";
    ss << "}\n";
    
    return ss.str();
}

std::string BalsamiqControlData::getCustomID()
{
    return getPropertyDic()->valueForKey("customID")->getCString();
}

std::string BalsamiqControlData::getText()
{
    return getPropertyDic()->valueForKey("text")->getCString();
}