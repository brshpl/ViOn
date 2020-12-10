//
// Created by Dashik on 12.11.2020.
//
#include "FileController/ChangeApplier.h"
#include "FileController/Parser.h"
#include <utility>

ChangeApplier::ChangeApplier(Change ch, std::shared_ptr<FileStorage> file) {
    ch_ = ch;
    file_ = std::move(file);
}

bool ChangeApplier::applyChange() {
    switch (ch_.cmd) {
        case INSERT_SYMBOL:
        {
            InsertChar insertChar((*file_), ch_);
            if (insertChar.insertSymbol()){
                ch_ = insertChar.getChange();
                *file_ = insertChar.getFile();
                return true;
            }
            else
                return false;
        }
        case DELETE_SYMBOL:{
            DeleteChar deleteChar((*file_), ch_);
            if (deleteChar.deleteSymbol()){
                ch_ = deleteChar.getChange();
                *file_ = deleteChar.getFile();
                return true;
            }
            else
                return false;
        }
        default:
            return false;
    }
}

Change ChangeApplier::getChange() {
    return ch_;
}

FileStorage ChangeApplier::getFile() {
    return *file_;
}

