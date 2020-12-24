
//
// Created by Dashik on 12.11.2020.
//

#include "FileController/TextManager.h"
FileStorage::FileStorage(size_t file_id) {
    SymbolState symbol = {'\0', true, 0};
    symbols.emplace_back(symbol);
    symbols_length = 0;
    file_id = file_id;
}

//void TextManagerClient::upDate() {
//    ParserForEditor parser(ch_, file_);
//    std::vector<Symbol> text = parser.parse();
//    TextEditor.upDate(text);
//}
//
//void TextManagerClient::setChange(Change ch) {
//    ch_ = ch;
//}
//
//void TextManagerClient::setFile(FileStorage file) {
//    file_ = file;
//}