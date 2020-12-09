//
// Created by Dashik on 12.11.2020.
//

#include "FileController/Parser.h"

#include <utility>

Parser::Parser(Change ch) {
    m_ch = ch;
};

ParserForEditor::ParserForEditor(Change ch, FileStorage file) : Parser(ch){
    m_file = std::move(file);
};

std::vector<Text> ParserForEditor::parse() {
    std::vector<Text> file;
    Text text{};
    for (auto & symbol : m_file.symbols){
        if (symbol.is_visible){
            text.symbol = symbol.symbol;
            text.symbolId =symbol.id;
            file.push_back(text);
        }
    }
    return file;
}

ParserToJson::ParserToJson(Change ch) : Parser(ch){}

json ParserToJson::parse() {
    json j =  {{"cmd", m_ch.cmd},
              {"fileId", m_ch.fileId},
              {"position",
                      {"symbolId", m_ch.position.symbolId}
              },
              {"newSymbolId", m_ch.newSymbolId},
              {"symbol"}, m_ch.symbol};
    return j;
}

ParserFromJson::ParserFromJson(Change ch, const json &j) : Parser(ch) {
    m_j = j;
}

Change ParserFromJson::parse() {
    m_ch.cmd = m_j["cmd"].get<Command>();
    m_ch.fileId = m_j["fileId"].get<size_t>();
    m_ch.position.symbolId = m_j["position"]["symbolId"].get<size_t>();
    m_ch.newSymbolId = m_j["newSymbolId"].get<size_t>();
    m_ch.symbol = m_j["symbol"].get<char>();
    return m_ch;
}


