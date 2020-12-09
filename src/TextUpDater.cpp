//
// Created by Dashik on 12.11.2020.
//

#include <FileController/TextUpDater.h>

#include <utility>
#include <memory>

TextUpDater::TextUpDater(FileStorage file, Change ch) {
    file_ = std::move(file);
    ch_ = ch;
}

Change TextUpDater::getChange() {
    return ch_;
}

FileStorage TextUpDater::getFile() {
    return file_;
}

InsertChar::InsertChar(FileStorage &file, Change &ch) : TextUpDater(std::move(file), ch){};


Change InsertChar::addNewId() {
    file_.symbols_length++;
    ch_.newSymbolId = file_.symbols_length;
    return ch_;
}

void InsertChar::insertSymbol() {
    ch_ = addNewId();
    SymbolState new_char{
        ch_.symbol,
        true,
        ch_.newSymbolId,
    };
    std::vector<SymbolState> &curFile = file_.symbols;
    for (auto iter = curFile.begin();
         iter != curFile.end(); ++iter){
        if (iter->id == ch_.position.symbolId){
            curFile.insert(iter, new_char);
            return;
        }
    }
}

DeleteChar::DeleteChar(FileStorage file, Change ch) : TextUpDater(std::move(file), ch){};

void DeleteChar::deleteSymbol() {
    for (auto & symbol : file_.symbols){
        if (symbol.id == ch_.position.symbolId)
            symbol.is_visible = false;
    }
}