#ifndef JSON_PARSER_H
#define JSON_PARSER_H

#include <string>
#include "Message.h"

class JsonParser {
public:
    JsonParser() = default;
    ~JsonParser() = default;
    std::string_view ParseToJson(const Change& ch);
    Change ParseFromJson(const std::string_view& change);
};

#endif
