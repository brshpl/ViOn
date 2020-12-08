//
// Created by Dashik on 12.11.2020.
//

#ifndef VION_PARSER_H
#define VION_PARSER_H

#include "TextManager.h"

class Parser{
public:
    Parser(Change ch, FileStorage file);
    virtual ~Parser(){};
    virtual std::string parse() = 0;
protected:
    Change m_ch;
    FileStorage m_file;
};

class ParserFile : public Parser{
public:
    ParserFile(Change ch, FileStorage file);
    ~ParserFile() override{};
    std::string parse() override;
};

#endif //VION_PARSER_H
