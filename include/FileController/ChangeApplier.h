#ifndef VION_CHANGEAPPLIER_H
#define VION_CHANGEAPPLIER_H

#include <memory>
#include "Message.h"
#include "FileStorage.h"

class ChangeApplier {
public:
    ChangeApplier(const Change &ch, std::shared_ptr<FileStorage> file);
    ~ChangeApplier() = default;
    bool applyChange();
    Change getChange() const;
    FileStorage getFile();
    Change ch_{};
    std::shared_ptr<FileStorage> file_;
};

#endif  // VION_CHANGEAPPLIER_H
