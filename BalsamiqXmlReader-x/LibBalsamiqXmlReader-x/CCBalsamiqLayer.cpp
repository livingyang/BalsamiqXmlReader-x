/*
 *  CCBalsamiqLayer.cpp
 *  BalsamiqReaderWithCocos2dx
 *
 *  Created by 青宝 中 on 12-4-23.
 *  Copyright 2012年 __MyCompanyName__. All rights reserved.
 *
 */

#include "CCBalsamiqLayer.h"
#include "BalsamiqBmmlData.h"

USING_NS_CC;

using std::string;

CCBalsamiqLayer::CCBalsamiqLayer():
balsamiqControlDic(new CCDictionary())
{
}

CCBalsamiqLayer::~CCBalsamiqLayer()
{
    CC_SAFE_RELEASE(balsamiqControlDic);
}

void CCBalsamiqLayer::setBalsamiqControl(const std::string &controlType, const std::string &controlName, CCNode *control)
{
    if (controlType.length() == 0 || controlName.length() == 0)
    {
        return;
    }
    
    CCObject *controlsDic = this->getBalsamiqControlDic()->objectForKey(controlType);
    
    if (controlsDic == NULL)
    {
        CCDictionary *dic = CCDictionary::create();
        dic->setObject(control, controlName);
        this->getBalsamiqControlDic()->setObject(dic, controlType);
    }
    else
    {
        static_cast<CCDictionary *>(controlsDic)->setObject(control, controlName);
    }
}

CCNode *CCBalsamiqLayer::getBalsamiqControl(const std::string &controlType, const std::string &controlName) const
{
    if (controlType.length() == 0 || controlName.length() == 0)
    {
        return NULL;
    }
    
    CCObject *controlsDic = this->getBalsamiqControlDic()->objectForKey(controlType);
    
    if (controlsDic == NULL)
    {
        return NULL;
    }
    else
    {
        return static_cast<CCNode *>(static_cast<CCDictionary *>(controlsDic)->objectForKey(controlName));
    }
}

#pragma mark -
#pragma mark CCBalsamiqLayerCreator

CCBalsamiqLayerCreator::~CCBalsamiqLayerCreator()
{}

CCBalsamiqLayerCreator *CCBalsamiqLayerCreator::sharedBalsamiqLayerCreator()
{
    static CCBalsamiqLayerCreator *creator = NULL;
    
    if (creator == NULL)
    {
        creator = new CCBalsamiqLayerCreator();
    }
    
    return creator;
}

CCBalsamiqLayer *CCBalsamiqLayerCreator::createBalsamiqLayer(BalsamiqBmmlData *bmmlData)
{
    CCBalsamiqLayer *layer = CCBalsamiqLayer::create();
    
    for (int i = 0; i < bmmlData->getControlDataArray()->count(); ++i)
    {
        BalsamiqControlData *controlData = static_cast<BalsamiqControlData *>(bmmlData->getControlDataArray()->objectAtIndex(i));
        
        string handleName = getControlHandleName(controlData);
        
        if (controlHandles.find(handleName) != controlHandles.end())
        {
            CCNode *node = controlHandles[handleName](layer, controlData);
            
            layer->setBalsamiqControl(handleName, controlData->getCustomID(), node);
        }
    }
    
    return layer;
}

cocos2d::CCLabelTTF *CCBalsamiqLayerCreator::getLabelFromLayer(CCBalsamiqLayer *layer, std::string name)
{   
    return static_cast<CCLabelTTF *>(layer->getBalsamiqControl(labelHandleName(), name));
}

cocos2d::CCMenuItem *CCBalsamiqLayerCreator::getButtonFromLayer(CCBalsamiqLayer *layer, std::string name)
{
    return static_cast<CCMenuItem *>(layer->getBalsamiqControl(buttonHandelName(), name));
}

std::string CCBalsamiqLayerCreator::getControlHandleName(BalsamiqControlData *controlData)
{
    std::string type = controlData->getAttributeDic()->valueForKey("controlTypeID")->getCString();
    type = type.substr(type.rfind(":") + 1);
    
    std::string subType = controlData->getPropertyDic()->valueForKey("customData")->getCString();

    return (subType.length() == 0) ? type : type.append(":").append(subType);
}

std::string CCBalsamiqLayerCreator::labelHandleName()
{
    return "Label";
}

std::string CCBalsamiqLayerCreator::imageHandleName()
{
    return "Image";
}

std::string CCBalsamiqLayerCreator::buttonHandelName()
{
    return "Image:button";
}

#pragma mark -
#pragma mark BalsamiqControl handles

CCNode *createLabelToLayer(CCBalsamiqLayer *layer, BalsamiqControlData *controlData)
{
    CCNode *node = CCLabelTTF::create("Test", "arial", 32);
    
    node->setPosition(ccp(100, 200));
    layer->addChild(node);
    
    return node;
}

CCNode *createImageToLayer(CCBalsamiqLayer *layer, BalsamiqControlData *controlData)
{
    CCSprite *sprite = CCSprite::create("Icon-57.png");
    
    sprite->setPosition(ccp(100, 100));
    layer->addChild(sprite);
    
    return sprite;
}

CCNode *createButtonToLayer(CCBalsamiqLayer *layer, BalsamiqControlData *controlData)
{
    CCMenu *menu = CCMenu::create();
    menu->setAnchorPoint(CCPointZero);
    menu->setPosition(CCPointZero);
    
    CCMenuItemImage *button = CCMenuItemImage::create("Icon-57.png", "Icon-57.png");
    menu->addChild(button);
    
    button->setPosition(ccp(200, 100));
    
    layer->addChild(menu);
    
    return button;
}

CCBalsamiqLayerCreator::CCBalsamiqLayerCreator()
{
    controlHandles[labelHandleName()] = &createLabelToLayer;
    controlHandles[imageHandleName()] = &createImageToLayer;
    controlHandles[buttonHandelName()] = &createButtonToLayer;
}
