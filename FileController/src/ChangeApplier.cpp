//
// Created by Dashik on 12.11.2020.
//
#include "FileController/ChangeApplier.h"
#include "FileController/Parser.h"
#include "FileController/Handler.h"
#include <memory>
#include <utility>

ChangeApplier::ChangeApplier(const Change &ch, std::shared_ptr<FileStorage> file) : ch_(ch), file_(std::move(file)){}

bool ChangeApplier::applyChange() {
    auto insertChar = std::make_shared<InsertSymbol>(ch_, file_.get());
    auto deleteChar = std::make_shared<DeleteSymbol>(ch_, file_.get());
    insertChar->SetNext(deleteChar);
    return selector(*insertChar, ch_);
}

Change ChangeApplier::getChange() const {
    return ch_;
}

FileStorage ChangeApplier::getFile() {
    return *file_;
}
