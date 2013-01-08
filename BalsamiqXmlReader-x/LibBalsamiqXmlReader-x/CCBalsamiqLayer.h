/*
 *  CCBalsamiqLayer.h
 *  BalsamiqReaderWithCocos2dx
 *
 *  Created by 青宝 中 on 12-4-23.
 *  Copyright 2012年 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef BalsamiqReaderWithCocos2dx_CCBalsamiqLayer_cpp
#define BalsamiqReaderWithCocos2dx_CCBalsamiqLayer_cpp

#include "cocos2d.h"

class BalsamiqBmmlData;
class CCBalsamiqLayer : public cocos2d::CCLayer
{    
public:
    CCBalsamiqLayer();
    virtual ~CCBalsamiqLayer();
    
    void setBalsamiqControl(const std::string &controlType, const std::string &controlName, CCNode *control);
    CCNode *getBalsamiqControl(const std::string &controlType, const std::string &controlName) const;
    
    CREATE_FUNC(CCBalsamiqLayer);
    
    CC_SYNTHESIZE_READONLY(cocos2d::CCDictionary *, balsamiqControlDic, BalsamiqControlDic);
};

class BalsamiqControlData;
typedef cocos2d::CCNode *BalsamiqControlHandleFunc(CCBalsamiqLayer *, BalsamiqControlData *);
typedef std::map<std::string /*handle name*/, BalsamiqControlHandleFunc */*handle func*/> BalsamiqControlHandleNameAndFuncDic;

class CCBalsamiqLayerCreator : public cocos2d::CCLayer
{
public:
    ~CCBalsamiqLayerCreator();
    
    static CCBalsamiqLayerCreator *sharedBalsamiqLayerCreator();
    
    CCBalsamiqLayer *createBalsamiqLayer(BalsamiqBmmlData *bmmlData);
    
    cocos2d::CCLabelTTF *getLabelFromLayer(CCBalsamiqLayer *layer, std::string name);
    cocos2d::CCMenuItem *getButtonFromLayer(CCBalsamiqLayer *layer, std::string name);
    
private:
    CCBalsamiqLayerCreator();
    
    std::string getControlHandleName(BalsamiqControlData *controlData);
    std::string getControlName(BalsamiqControlData *controlData);
    
    std::string labelHandleName();
    std::string imageHandleName();
    std::string buttonHandelName();
    
private:
    BalsamiqControlHandleNameAndFuncDic controlHandles;
};

#endif //BalsamiqReaderWithCocos2dx_CCBalsamiqLayer_cpp