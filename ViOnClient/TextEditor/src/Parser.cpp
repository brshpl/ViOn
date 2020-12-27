#include "Parser.h"


Parser::Parser(const Change& ch) {
    ch_ = ch;
};

ParserForEditor::ParserForEditor(const Change& ch, std::shared_ptr<FileStorage> file) : Parser(ch), file_(file) {};


std::vector<std::vector<Symbol>> ParserForEditor::parse() {
    std::vector<std::vector<Symbol>> file;
    Symbol text {};
    std::vector<Symbol> string;

    for (auto& symbol : file_->symbols) {
        if (symbol.is_visible) {
            text.symbol = symbol.symbol;
            text.symbolId =symbol.id;
            string.push_back(text);
        }
        if (symbol.symbol == '\n' || symbol.symbol == '\0') {
            file.push_back(string);
            string.clear();
        }
    }

    return file;
}
