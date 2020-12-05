//
// Created by Dashik on 12.11.2020.
//

#include "TextUpDater.h"

#include <utility>

TextUpDater::TextUpDater(FileStorage file, Change ch) {
    m_file = std::move(file);
    m_ch = ch;
}

InsertChar::InsertChar(FileStorage file, Change ch) : TextUpDater(std::move(file), ch){};

char InsertChar::getSymbol() {
    return m_ch.symbol;
}

Change InsertChar::add_new_id() {
    m_ch.symbolId = m_file.max_id;
    return m_ch;
}

void InsertChar::insertSymbol() {
    SymbolState new_char{
        new_char.symbol =
    }
}

DeleteChar::DeleteChar(FileStorage file, Change ch) : TextUpDater(std::move(file), ch){};

