
#include <FileController/Message.h>
#include <FileController/FileStorage.h>
#include <memory>
#include <FileController/ChangeApplier.h>
#include <FileController/Handler.h>

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
