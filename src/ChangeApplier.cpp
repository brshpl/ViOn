//
// Created by Dashik on 12.11.2020.
//

#include "ChangeApplier.h"

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
            break;
        }
        case DELETE_SYMBOL:{
            DeleteChar deleteChar(m_file, m_ch);
            deleteChar.deleteSymbol();
            break;
        }
        default:
            return false;
    }

}

