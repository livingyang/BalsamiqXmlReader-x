/*
 *  BalsamiqFileManager.h
 *  BalsamiqReaderWithCocos2dx
 *
 *  Created by 青宝 中 on 12-4-9.
 *  Copyright 2012年 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef BalsamiqReaderWithCocos2dx_BalsamiqFileManager_cpp
#define BalsamiqReaderWithCocos2dx_BalsamiqFileManager_cpp

#include "cocos2d.h"
#include <libxml/parser.h>

class BalsamiqControlData;
class BalsamiqFileManager : public cocos2d::CCObject
{
public:
    virtual ~BalsamiqFileManager();
    
    static BalsamiqFileManager *sharedBalsamiqFileManager();
    
    cocos2d::CCArray *getControlDataFromFileName(std::string bmmlFileName);
    
    cocos2d::CCArray *parseFileControlInfo(std::string filePath);
private:
    BalsamiqFileManager();
    void loadAllControlInfo(std::string rootDir);
    
    typedef std::map<std::string /*fileName*/, std::string /*filePath*/> NameToPathMap;
    void makeBmmlFileList(std::string dir, NameToPathMap &nameToPathMap);
    void printNameToPathMap(NameToPathMap &nameToPathMap) const;
    BalsamiqControlData *parseControlInfo(xmlNodePtr node);
    
private:
    typedef cocos2d::CCDictionary FileNameAndControlDic;
    FileNameAndControlDic *allControlInfo;
    
    //CC_SYNTHESIZE_READONLY(FileNameAndControlDic *, allControlInfo, AllControlInfo);
};

#endif //BalsamiqReaderWithCocos2dx_BalsamiqFileManager_cpp