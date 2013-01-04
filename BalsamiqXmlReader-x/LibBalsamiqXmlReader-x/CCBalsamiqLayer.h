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

struct ICCBalsamiqLayerDelegate
{
    virtual void OnButtonClick(std::string name, cocos2d::CCMenuItemImage *button) = 0;
};

class CCBalsamiqLayer : public cocos2d::CCLayer
{    
public:
    CCBalsamiqLayer();
    virtual ~CCBalsamiqLayer();
    
    bool initWithBalsamiqFile(std::string fileName, ICCBalsamiqLayerDelegate *delegate);
    static CCBalsamiqLayer *layerWithBalsamiqFile(std::string fileName, ICCBalsamiqLayerDelegate *delegate);
    
    cocos2d::CCNode *getControlByName(std::string name);
    
private:
    ICCBalsamiqLayerDelegate *m_pDelegate;
    
    cocos2d::CCDictionary *mNameAndNodeDic;
};

#endif //BalsamiqReaderWithCocos2dx_CCBalsamiqLayer_cpp