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

InsertChar::InsertChar(FileStorage file, Change ch) : TextUpDater(std::move(file), ch){};

char InsertChar::getSymbol() {
    return m_ch.symbol;
}

Change InsertChar::add_new_id() {
    m_file.symbols_length++;
    m_ch.symbolId = m_file.symbols_length;
    return m_ch;
}

void InsertChar::insertSymbol() {
    m_ch = add_new_id();
    SymbolState new_char{
        m_ch.symbol,
        true,
        m_ch.symbolId
    };
    for (auto iter = m_file.strings[m_ch.stringId].symbols.begin();
         iter != m_file.strings[m_ch.stringId].symbols.end(); ++iter){
        if (iter->id == m_ch.behind_symbol_id)
            m_file.strings[m_ch.stringId].symbols.insert(iter, new_char);
    }
}

DeleteChar::DeleteChar(FileStorage file, Change ch) : TextUpDater(std::move(file), ch){};

void DeleteChar::deleteSymbol() {
    for (auto & symbol : m_file.strings[m_ch.stringId].symbols){
        if (symbol.id == m_ch.symbolId)
            symbol.is_visible = false;
    }
}