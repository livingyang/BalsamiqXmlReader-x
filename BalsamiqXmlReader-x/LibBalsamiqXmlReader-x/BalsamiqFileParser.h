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

#include <string>
#include <map>

typedef std::map<std::string /*property name*/, std::string /*property value*/> NameValueMap;

class BalsamiqFileParser
{    
public:
    BalsamiqFileParser();
    virtual ~BalsamiqFileParser();
    
    bool parseXmlString(const char *xmlString, NameValueMap &outMap);
};

#endif //BalsamiqXmlReader_x_BalsamiqFileParser_cpp