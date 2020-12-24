// Created by Dashik on 12.11.2020.
//

#include "FileController/Parser.h"

#include <utility>

Parser::Parser(Change ch) {
    ch_ = ch;
};

ParserForEditor::ParserForEditor(Change ch, FileStorage file) : Parser(ch){
    file_ = std::move(file);
};

std::vector<std::vector<Symbol>> ParserForEditor::parse() {
    std::vector<std::vector<Symbol>> file;
    file.reserve(file_.symbols.size());
    Symbol text{};
    std::vector<Symbol> string;
    for (auto & symbol : file_.symbols){
        if (symbol.is_visible){
            text.symbol = symbol.symbol;
            text.symbol_id =symbol.id;
            string.push_back(text);
        }
        if (symbol.symbol == '\n'){
            file.push_back(string);
            string.clear();
        }
    }
    return file;
}