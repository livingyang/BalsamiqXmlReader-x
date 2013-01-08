/*
 *  BalsamiqBmmlData.h
 *  BalsamiqXmlReader-x
 *
 *  Created by 中 青宝 on 13-1-5.
 *  Copyright 2013年 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef BalsamiqXmlReader_x_BalsamiqBmmlData_cpp
#define BalsamiqXmlReader_x_BalsamiqBmmlData_cpp

#include "cocos2d.h"

class BalsamiqBmmlData : public cocos2d::CCObject
{    
public:
    BalsamiqBmmlData();
    virtual ~BalsamiqBmmlData();
    
    static BalsamiqBmmlData *create();
    std::string description();
    
    CC_SYNTHESIZE_RETAIN(cocos2d::CCArray*, controlDataArray, ControlDataArray);
    
    CC_PROPERTY_PASS_BY_REF(std::string, bmmlFilePath, BmmlFilePath);
    CC_SYNTHESIZE_READONLY(std::string, bmmlFileDic, BmmlFileDic);
    CC_SYNTHESIZE_READONLY(std::string, bmmlFileName, BmmlFileName);
};

class BalsamiqControlData : public cocos2d::CCObject
{
public:
    BalsamiqControlData();
    virtual ~BalsamiqControlData();
    
    static BalsamiqControlData *create();
    std::string description();
    
    CC_SYNTHESIZE_RETAIN(cocos2d::CCDictionary*, attributeDic, AttributeDic);
    CC_SYNTHESIZE_RETAIN(cocos2d::CCDictionary*, propertyDic, PropertyDic);
    
    CC_PROPERTY_READONLY(std::string, customID, CustomID);
    CC_PROPERTY_READONLY(std::string, text, Text);
};

#endif //BalsamiqXmlReader_x_BalsamiqBmmlData_cpp