#include "TextEditor/Parser.h"

////
#include <fstream>
extern std::ofstream err;
////

//Parser::Parser(const Change& ch) {
//    ch_ = ch;
//};

ParserForEditor::ParserForEditor(std::shared_ptr<FileStorage> file) : file_(file) {};


void ParserForEditor::parse(std::vector<std::vector<Symbol>>& file) {
    Symbol text {};
    std::vector<Symbol> string;

    for (auto& symbol : file_->symbols) {
        if (symbol.is_visible) {
            text.symbol = symbol.symbol;
            text.symbolId =symbol.id;
            if (text.symbol != '\0') string.push_back(text);
        }
        if (symbol.symbol == '\n' || symbol.symbol == '\0') {
//            for (auto s : string) {
//                err << s.symbol;
//            } err << std::endl;
            file.push_back(string);
            string.clear();
        }
    }

    std::string str1;
    for (auto str : file) {
        for (auto symbol : str) {
            str1.push_back(symbol.symbol);
        }
    }
    err << "file:_____" << str1 << std::endl;

    for (auto i : file_->symbols) {
        if (i.symbol != '\0') {
            err << i.symbol;
        }
    }

}
