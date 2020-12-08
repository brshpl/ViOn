//
// Created by Dashik on 12.11.2020.
//

#include "TextUpDater.h"

#include <utility>
#include <memory>

TextUpDater::TextUpDater(FileStorage file, Change ch) {
    m_file = std::move(file);
    m_ch = ch;
}

Change TextUpDater::getChange() {
    return m_ch;
}

FileStorage TextUpDater::getFile() {
    return m_file;
}

InsertChar::InsertChar(FileStorage &file, Change &ch) : TextUpDater(std::move(file), ch){};

char InsertChar::getSymbol() {
    return m_ch.symbol;
}

Change InsertChar::add_new_id() {
    m_file.symbols_length++;
    m_ch.newSymbolId = m_file.symbols_length;
    return m_ch;
}

void InsertChar::insertSymbol() {
    m_ch = add_new_id();
    SymbolState new_char{
        m_ch.symbol,
        true,
        m_ch.newSymbolId,
    };
    std::vector<SymbolState> &curFile = m_file.symbols;
    for (auto iter = curFile.begin();
         iter != curFile.end(); ++iter){
        if (iter->id == m_ch.position.symbolId){
            curFile.insert(iter, new_char);
            return;
        }
    }
}

DeleteChar::DeleteChar(FileStorage file, Change ch) : TextUpDater(std::move(file), ch){};

void DeleteChar::deleteSymbol() {
    for (auto & symbol : m_file.symbols){
        if (symbol.id == m_ch.position.symbolId)
            symbol.is_visible = false;
    }
}