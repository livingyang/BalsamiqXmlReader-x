/*
 *  BalsamiqReaderConfig.cpp
 *  BalsamiqReaderWithCocos2dx
 *
 *  Created by 青宝 中 on 12-4-9.
 *  Copyright 2012年 __MyCompanyName__. All rights reserved.
 *
 */

#include "BalsamiqReaderConfig.h"
USING_NS_CC;

BalsamiqReaderConfig::BalsamiqReaderConfig()
{
}

BalsamiqReaderConfig::~BalsamiqReaderConfig()
{
}

BalsamiqReaderConfig *BalsamiqReaderConfig::sharedBalsamiqReaderConfig()
{
    static BalsamiqReaderConfig *config = NULL;
    
    if (config == NULL)
    {
        config = new BalsamiqReaderConfig();
    }
    
    return  config;
}

void BalsamiqReaderConfig::loadConfig(std::string configFilePath)
{
    CCDictionary *configInfo = CCDictionary::createWithContentsOfFile(configFilePath.c_str());
    
    if (configInfo == NULL || configInfo->count() == 0)
    {
        CCLog("BalsamiqReaderConfig::loadConfig file path = %s is invalid.", configFilePath.c_str());
        return;
    }
    
    this->setRootDir(static_cast<CCString *>(configInfo->objectForKey("RootDir"))->getCString());
}