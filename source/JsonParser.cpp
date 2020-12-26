#include "JsonParser.hpp"
#include "json.hpp"
#include <iostream>

// for convenience
using json = nlohmann::json;

std::string JsonParser::ParseToJson(const Change& ch) {
    json j =  json::object({
            {"cmd", ch.cmd},
            {"fileId", ch.fileId},
            {"position", {
                {"symbolId", ch.position.symbolId},
                {"stringId", ch.position.stringId}
                }
            },
            {"symbol", ch.symbol}
        });
    return j.dump();
}

Change JsonParser::ParseFromJson(const std::string_view& change) {
    json j = json::parse(change);
    Change result;
    result.cmd = j["cmd"].get<Command>();
    result.fileId = j["fileId"].get<size_t>();
    result.position = Position{j["position"]["symbolId"].get<size_t>(),
                               j["position"]["stringId"].get<size_t>()};
    result.symbol = j["symbol"].get<char>();
    return result;
}
