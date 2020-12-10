//
// Created by Dashik on 12.11.2020.
//

#include <FileController/TextUpDater.h>

#include <utility>
#include <memory>
#include <algorithm>

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

bool InsertChar::insertSymbol() {
    std::list<SymbolState> &curFile = file_.symbols;
    auto result = std::find_if(curFile.begin(), curFile.end(), [foo = ch_.position.symbolId](SymbolState s){return s.id == foo;});
    if (result == curFile.end())
        return false;
    else{
        ch_ = addNewId();
        SymbolState new_char{
            ch_.symbol,
            true,
            ch_.newSymbolId,
            };
        curFile.insert(result, new_char);
        return true;
    }
}

DeleteChar::DeleteChar(FileStorage file, Change ch) : TextUpDater(std::move(file), ch){};

bool DeleteChar::deleteSymbol() {
    auto result = std::find_if(file_.symbols.begin(), file_.symbols.end(), [foo = ch_.position.symbolId](SymbolState s){return s.id == foo;});
    if (result == file_.symbols.end())
        return false;
    else{
        result->is_visible = false;
        return true;
    }
}