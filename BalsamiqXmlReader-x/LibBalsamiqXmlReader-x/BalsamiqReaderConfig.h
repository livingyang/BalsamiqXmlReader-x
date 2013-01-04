/*
 *  BalsamiqReaderConfig.h
 *  BalsamiqReaderWithCocos2dx
 *
 *  Created by 青宝 中 on 12-4-9.
 *  Copyright 2012年 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef BalsamiqReaderWithCocos2dx_BalsamiqReaderConfig_cpp
#define BalsamiqReaderWithCocos2dx_BalsamiqReaderConfig_cpp

#include "cocos2d.h"

class BalsamiqReaderConfig : public cocos2d::CCObject
{    
    CC_SYNTHESIZE_PASS_BY_REF(std::string, rootDir, RootDir);
    
public:
    virtual ~BalsamiqReaderConfig();

private:
    BalsamiqReaderConfig();
    
public:
	static BalsamiqReaderConfig *sharedBalsamiqReaderConfig();

    void loadConfig(std::string configFilePath);
};

#endif //BalsamiqReaderWithCocos2dx_BalsamiqReaderConfig_cpp