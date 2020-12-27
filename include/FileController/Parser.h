#pragma once

#include <vector>
#include "Message.h"
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
    ParserForEditor(Change ch, FileStorage file) : Parser(ch), file_(file) {};
    ~ParserForEditor() override{};
    std::vector<Symbol> parse();
private:
    FileStorage file_;
};
