/*
 *  BalsamiqFileParser.h
 *  BalsamiqXmlReader-x
 *
 *  Created by 中 青宝 on 13-1-4.
 *  Copyright 2013年 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef BalsamiqXmlReader_x_BalsamiqFileParser_cpp
#define BalsamiqXmlReader_x_BalsamiqFileParser_cpp

#include "cocos2d.h"
#include <libxml/parser.h>

class BalsamiqControlData;
class BalsamiqBmmlData;
class BalsamiqFileParser : public cocos2d::CCObject
{    
public:
    BalsamiqFileParser();
    virtual ~BalsamiqFileParser();
    
    static BalsamiqFileParser *sharedBalsamiqFileParser();
    
    BalsamiqBmmlData *parseBmmlFile(std::string bmmlFilePath);
    
private:
    cocos2d::CCArray *parseFileControlInfo(std::string filePath);
    BalsamiqControlData *parseControlInfo(xmlNodePtr node);
};

#endif //BalsamiqXmlReader_x_BalsamiqFileParser_cpp