//
// Created by Dashik on 12.11.2020.
//

#ifndef VION_CHANGEAPPLIER_H
#define VION_CHANGEAPPLIER_H
#include "TextManager.h"
#include "TextUpDater.h"
#include <memory>

class ChangeApplier {
public:
    ChangeApplier(const Change &ch, std::unique_ptr<FileStorage> file);
    ~ChangeApplier() = default;
    bool applyChange();
    Change getChange();
    FileStorage getFile();

private:
    Change ch_{};
    std::unique_ptr<FileStorage> file_;
};


#endif //VION_CHANGEAPPLIER_H
