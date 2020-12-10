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
    size_t symbol_id;
};

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
    std::vector<Text> parse();
private:
    FileStorage file_;
};

class ParserToJson : public Parser{
public:
    explicit ParserToJson(Change ch);
    json parse();
};

class ParserFromJson{
public:
    explicit ParserFromJson(const json &j);
    Change parse();
private:
    json j_;
};
#endif //VION_PARSER_H
