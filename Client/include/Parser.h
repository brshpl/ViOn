#ifndef SERVER_PARSER_INCLUDE_H_
#define SERVER_PARSER_INCLUDE_H_

#include <string>

#include "FileController/FileStorage.h"


std::string ParserToJson(const Change& ch);
Change ParserFromJson(const std::string& j);

//class Parser {
//    explicit Parser(Change ch);
//
//protected:
//    Change ch_;
//};
//
//class ParserToJson: public Parser {
//public:
//    explicit ParserToJson(Change ch);
//    json parse();
//};
//
//class ParserFromJson {
//public:
//    explicit ParserFromJson(const json &j);
//    Change parse();
//private:
//    json j_;
//};

#endif  // SERVER_PARSER_INCLUDE_H_
