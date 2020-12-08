//
// Created by Dashik on 12.11.2020.
//
#include "ChangeApplier.h"
#include "Parser.h"
#include <utility>

ChangeApplier::ChangeApplier(Change ch, struct FileStorage file) {
    m_ch = ch;
    m_file = std::move(file);
}

FileStorage ChangeApplier::applyChange() {
    switch (m_ch.cmd) {
        case INSERT_SYMBOL:
        {
            InsertChar insertChar(m_file, m_ch);
            insertChar.insertSymbol();
            m_ch = insertChar.getChange();
            m_file = insertChar.getFile();
            break;
        }
        case DELETE_SYMBOL:{
            DeleteChar deleteChar(m_file, m_ch);
            deleteChar.deleteSymbol();
            m_ch = deleteChar.getChange();
            m_file = deleteChar.getFile();
            break;
        }
        default:
            return m_file;
    }
    ParserForEditor parser(m_ch, m_file);
    std::string str = parser.parse();
    std::cout << str << std::endl;
    return m_file;
}

