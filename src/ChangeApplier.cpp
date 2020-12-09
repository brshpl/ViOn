//
// Created by Dashik on 12.11.2020.
//
#include "FileController/ChangeApplier.h"
#include "FileController/Parser.h"
#include <utility>

ChangeApplier::ChangeApplier(Change ch, struct FileStorage file) {
    m_ch = ch;
    m_file = std::move(file);
}

bool ChangeApplier::applyChange() {
    switch (m_ch.cmd) {
        case INSERT_SYMBOL:
        {
            InsertChar insertChar(m_file, m_ch);
            insertChar.insertSymbol();
            m_ch = insertChar.getChange();
            m_file = insertChar.getFile();
            return true;
        }
        case DELETE_SYMBOL:{
            DeleteChar deleteChar(m_file, m_ch);
            deleteChar.deleteSymbol();
            m_ch = deleteChar.getChange();
            m_file = deleteChar.getFile();
            return true;
        }
        default:
            return false;
    }
}

Change ChangeApplier::getChange() {
    return m_ch;
}

FileStorage ChangeApplier::getFile() {
    return m_file;
}

