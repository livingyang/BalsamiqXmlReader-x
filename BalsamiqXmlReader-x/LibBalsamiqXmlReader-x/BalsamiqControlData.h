/*
 *  BalsamiqControlData.h
 *  BalsamiqReaderWithCocos2dx
 *
 *  Created by 青宝 中 on 12-4-9.
 *  Copyright 2012年 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef BalsamiqReaderWithCocos2dx_BalsamiqControlData_cpp
#define BalsamiqReaderWithCocos2dx_BalsamiqControlData_cpp

#include "cocos2d.h"

class BalsamiqControlData : public cocos2d::CCObject
{    
public:
    BalsamiqControlData();
    virtual ~BalsamiqControlData();
    
    static BalsamiqControlData *balsamiqControlData();
    void printData();
    std::string getStringData();
    
    CC_SYNTHESIZE_RETAIN(cocos2d::CCDictionary*, attributeDic, AttributeDic);
    CC_SYNTHESIZE_RETAIN(cocos2d::CCDictionary*, propertyDic, PropertyDic);
};

#endif //BalsamiqReaderWithCocos2dx_BalsamiqControlData_cpp