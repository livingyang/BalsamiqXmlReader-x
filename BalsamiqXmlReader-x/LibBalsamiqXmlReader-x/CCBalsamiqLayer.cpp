/*
 *  CCBalsamiqLayer.cpp
 *  BalsamiqReaderWithCocos2dx
 *
 *  Created by 青宝 中 on 12-4-23.
 *  Copyright 2012年 __MyCompanyName__. All rights reserved.
 *
 */

#include "CCBalsamiqLayer.h"

using namespace cocos2d;

CCBalsamiqLayer::CCBalsamiqLayer():
mNameAndNodeDic(new cocos2d::CCDictionary())
{
}

CCBalsamiqLayer::~CCBalsamiqLayer()
{
    CC_SAFE_RELEASE(mNameAndNodeDic);
}

bool CCBalsamiqLayer::initWithBalsamiqFile(std::string fileName, ICCBalsamiqLayerDelegate *delegate)
{
    return false;
}

CCBalsamiqLayer *CCBalsamiqLayer::layerWithBalsamiqFile(std::string fileName, ICCBalsamiqLayerDelegate *delegate)
{
    CCBalsamiqLayer *layer = new CCBalsamiqLayer();
    
    if (layer && layer->initWithBalsamiqFile(fileName, delegate))
    {
        layer->autorelease();
        return layer;
    }
    
    CC_SAFE_RELEASE(layer);
    return NULL;
}

cocos2d::CCNode *CCBalsamiqLayer::getControlByName(std::string name)
{
    return static_cast<CCNode *>(mNameAndNodeDic->objectForKey(name));
}