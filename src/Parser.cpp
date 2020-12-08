//
// Created by Dashik on 12.11.2020.
//

#include "Parser.h"

Parser::Parser(Change ch, FileStorage file) {
    m_ch = ch;
    m_file = std::move(file);
};

ParserFile::ParserFile(Change ch, FileStorage file) : Parser(ch, file){};

std::string ParserFile::parse() {
    std::string text_file;
    for (auto & string : m_file.strings){
        for (auto & symbol : string.symbols){
            if (symbol.is_visible)
                text_file += symbol.symbol;
        }
    }
    return text_file;
}

