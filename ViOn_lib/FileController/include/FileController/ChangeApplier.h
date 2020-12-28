#ifndef VION_CHANGEAPPLIER_H
#define VION_CHANGEAPPLIER_H

#include "TextUpDater.h"

#include <memory>


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