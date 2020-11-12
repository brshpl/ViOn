//
// Created by Dashik on 12.11.2020.
//

#ifndef VION_PARSER_H
#define VION_PARSER_H


class Parser{
public:
    Parser();
    virtual ~Parser();
    virtual void parse() = 0;
};

class ParserState : public Parser{
public:
    ParserState();
    ~ParserState();
    void parse() override;
};

#endif //VION_PARSER_H
