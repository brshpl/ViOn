//
// Created by yakovitskiy on 12.11.2020.
//

#ifndef VION_PARSER_H
#define VION_PARSER_H

#include "message.h"
#include "interpretator.h"
#include <vector>
#include <string>

class Parser {
public:
    Change virtual Parse(char &curChar, Mode &mode,
                         Position &position, std::string &buffer);
    bool virtual CanParse(char &curChar, Mode &mode,
                          Position &position, std::string &buffer);
    void AddParser(Parser&);
private:
    std::vector<Parser> parsers;
};

class ParseInsertSubString : virtual public Parser {
    Change Parse(char &curChar, Mode &mode,
                 Position &position, std::string &buffer) override;
    bool CanParse(char &curChar, Mode &mode,
                  Position &position, std::string &buffer) override;
};

class ParserDeleteSymbol : virtual public Parser {
    Change Parse(char &curChar, Mode &mode,
                 Position &position, std::string &buffer) override;
    bool CanParse(char &curChar, Mode &mode,
                  Position &position, std::string &buffer) override;
};

class ParserDeleteString : virtual public Parser {
    Change Parse(char &curChar, Mode &mode,
                 Position &position, std::string &buffer) override;
    bool CanParse(char &curChar, Mode &mode,
                  Position &position, std::string &buffer) override;
};

class ParserCreateFile : virtual public Parser {
    Change Parse(char &curChar, Mode &mode,
                 Position &position, std::string &buffer) override;
    bool CanParse(char &curChar, Mode &mode,
                  Position &position, std::string &buffer) override;
};

class ParserDeleteFile : virtual public Parser {
    Change Parse(char &curChar, Mode &mode,
                 Position &position, std::string &buffer) override;
    bool CanParse(char &curChar, Mode &mode,
                  Position &position, std::string &buffer) override;
};

#endif //VION_PARSER_H
