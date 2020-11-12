//
// Created by Dashik on 12.11.2020.
//

#include "Parser.h"
#include "TextManager.h"

class Parser{
public:
    Parser();
    virtual ~Parser();
    virtual auto parse() = 0;
};
class ParserState : public Parser{
public:
    ParserState();
    ~ParserState();
    TextStorage parse() override;
};