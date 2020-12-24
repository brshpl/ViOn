//
// Created by Dashik on 12.11.2020.
//

#ifndef VION_PARSER_H
#define VION_PARSER_H

#include "FileStorage.h"


class Parser{
public:
    Parser(Change ch);
    virtual ~Parser(){};
protected:
    Change ch_;
};

class ParserForEditor : public Parser{
public:
    ParserForEditor(Change ch, FileStorage file);
    ~ParserForEditor() override{};
    std::vector<std::vector<Symbol>> parse();
private:
    FileStorage file_;
};

#endif //VION_PARSER_H
