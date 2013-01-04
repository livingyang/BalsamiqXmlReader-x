/*
 *  BalsamiqControlData.cpp
 *  BalsamiqReaderWithCocos2dx
 *
 *  Created by 青宝 中 on 12-4-9.
 *  Copyright 2012年 __MyCompanyName__. All rights reserved.
 *
 */

#include "BalsamiqControlData.h"

using namespace cocos2d;

BalsamiqControlData::BalsamiqControlData():
attributeDic(NULL),
propertyDic(NULL)
{
    setAttributeDic(new CCDictionary());
    setPropertyDic(new CCDictionary());
}

BalsamiqControlData::~BalsamiqControlData()
{
    setAttributeDic(NULL);
    setPropertyDic(NULL);
}

BalsamiqControlData *BalsamiqControlData::balsamiqControlData()
{
    return static_cast<BalsamiqControlData *>((new BalsamiqControlData())->autorelease());
}

void printAllKeyAndValue(CCDictionary *dic)
{
    CCDictElement* pElement = NULL;
    CCDICT_FOREACH(dic, pElement)
    {
        CCString *value = (CCString *)pElement->getObject();
        printf("   %s = %s,\n", pElement->getStrKey(), value->getCString());
    }
}

void BalsamiqControlData::printData()
{
    printf("BalsamiqControlData = {\n");
    printf("attribute = {\n");
    printAllKeyAndValue(getAttributeDic());
    printf("},\n");
    
    printf("properties = {\n");
    printAllKeyAndValue(getPropertyDic());
    printf("}\n");
    printf("}\n");
}

void appendDictionaryDataToStream(CCDictionary *dic, std::stringstream &ss)
{
    CCDictElement* pElement = NULL;
    CCDICT_FOREACH(dic, pElement)
    {
        CCString *value = (CCString *)pElement->getObject();
        
        ss << "\t" << pElement->getStrKey() << " = " << value->getCString() << ",\n";
//        printf("   %s = %s,\n", pElement->getStrKey(), value->getCString());
    }
}

std::string BalsamiqControlData::getStringData()
{
    std::stringstream ss;
    
    ss << "{\n";
    ss <<"attribute = {\n";
//    printAllKeyAndValue(getAttributeDic());
    appendDictionaryDataToStream(getAttributeDic(), ss);
    ss << "},\n";
    
    ss << "properties = {\n";
//    printAllKeyAndValue(getPropertyDic());
    appendDictionaryDataToStream(getPropertyDic(), ss);
    ss << "}\n";
    ss << "}\n";
    
    return ss.str();
}
