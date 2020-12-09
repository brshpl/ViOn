//
// Created by Dashik on 12.11.2020.
//

#ifndef VION_PARSER_H
#define VION_PARSER_H

#include "TextManager.h"
#include <nlohmann/json.hpp>

using json = nlohmann::json;

struct Text{
    char symbol;
    size_t symbolId;
};

class Parser{
public:
    Parser(Change ch);
    virtual ~Parser(){};
protected:
    Change m_ch;
};

class ParserForEditor : public Parser{
public:
    ParserForEditor(Change ch, FileStorage file);
    ~ParserForEditor() override{};
    std::vector<Text> parse();
private:
    FileStorage m_file;
};

class ParserToJson : public Parser{
    explicit ParserToJson(Change ch);
    json parse();
};

class ParserFromJson : public Parser{
    explicit ParserFromJson(Change ch, const json &j);
    Change parse();
private:
    json m_j;
};
#endif //VION_PARSER_H
