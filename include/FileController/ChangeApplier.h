//
// Created by Dashik on 12.11.2020.
//

#ifndef VION_CHANGEAPPLIER_H
#define VION_CHANGEAPPLIER_H
#include "TextManager.h"
#include "TextUpDater.h"

class ChangeApplier {
public:
    ChangeApplier(Change ch, struct FileStorage file);
    ~ChangeApplier() = default;
    bool applyChange();
    Change getChange();
    FileStorage getFile();

private:
    Change m_ch{};
    FileStorage m_file;

};


#endif //VION_CHANGEAPPLIER_H
