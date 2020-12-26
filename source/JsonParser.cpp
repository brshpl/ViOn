#include "JsonParser.h"
#include "json.hpp"

// for convenience
using json = nlohmann::json;

std::string_view JsonParser::ParseToJson(const Change& ch) {
    json j =  {{"cmd", ch.cmd},
               {"fileId", ch.fileId},
               {"position",{
                               {"symbolId", ch.position.symbolId}}
               },
               {"newSymbolId", ch.position.symbolId},
               {"symbol", ch.symbol}};
    return j.dump();
}

Change JsonParser::ParseFromJson(const std::string_view& change) {
    json j = json::parse(change);
    Change m_ch {};
    m_ch.cmd = j["cmd"].get<Command>();
    m_ch.fileId = j["fileId"].get<size_t>();
    m_ch.position = Position {j["position"]["symbolId"].get<size_t>(), j["position"]["stringId"].get<size_t>()};
    m_ch.symbol = j["symbol"].get<char>();
    return m_ch;
}