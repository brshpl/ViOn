#ifndef PARSER_H
#define PARSER_H

#include "Message.h"
#include "Mode.h"
#include "Position.h"
#include <string>
#include <set>
#include <vector>

class Parser {
public:
    Parser() = default;
    ~Parser() = default;
    Change virtual Parse(char &curChar, Mode &mode,
                          Position &position, std::string &buffer);
    bool virtual CanParse(char &curChar, Mode &mode,
                          Position &position, std::string &buffer);
    void AddParser(Parser*);
private:
    std::vector<Parser*> parsers;
};

class ParseInsertSubString : public Parser {
public:
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

#endif // PARSER_H