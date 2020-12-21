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
    std::vector<Symbol> parse();
private:
    FileStorage file_;
};

//вынести из библиотеки
//class ParserToJson : public Parser{
//public:
//    explicit ParserToJson(Change ch);
//    json parse();
//};
//
//class ParserFromJson{
//public:
//    explicit ParserFromJson(const json &j);
//    Change parse();
//private:
//    json j_;
//};
#endif //VION_PARSER_H
