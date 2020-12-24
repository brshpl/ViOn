//
// Created by Dashik on 12.11.2020.
//

#include <FileController/TextUpDater.h>

#include <algorithm>

TextUpDater::TextUpDater(FileStorage* file, Change ch) {
    file_ = file;
    ch_ = ch;
}

Change TextUpDater::getChange() {
    return ch_;
}

FileStorage TextUpDater::getFile() {
    FileStorage* file = file_;
    return *file;
}

InsertChar::InsertChar(FileStorage* file, Change &ch) : TextUpDater(file, ch){};


Change InsertChar::addNewId() {
    file_->symbols_length++;
    ch_.newSymbolId = file_->symbols_length;
    return ch_;
}

bool InsertChar::insertSymbol() {
    std::list<SymbolState> &curFile = file_->symbols;
    auto result = std::find_if(curFile.begin(), curFile.end(), [foo = ch_.position.symbolId](SymbolState s){return s.id == foo;});
    if (result == curFile.end())
        return false;
    ch_ = addNewId();
    SymbolState new_char{
        ch_.symbol,
        true,
        ch_.newSymbolId,
        };
    curFile.insert(result, new_char);
    file_->symbols = curFile;
    return true;
}

DeleteChar::DeleteChar(FileStorage* file, Change ch) : TextUpDater(file, ch){};

bool DeleteChar::deleteSymbol() {
    auto result = std::find_if(file_->symbols.begin(), file_->symbols.end(), [foo = ch_.newSymbolId](SymbolState s){return s.id == foo;});
    if (result == file_->symbols.end())
        return false;
    else{
        result->is_visible = false;
        return true;
    }
}