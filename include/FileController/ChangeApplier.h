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
//    ChangeApplier(Change ch, IDGenerator idGen, TextManager manager);
    ~ChangeApplier();
    bool inputIdIntoChange();
    bool sendChange();
    Change m_ch{};
private:
    bool applyChange();
//    Change remove_id(Change ch, const FileStorage& file);
    char m_symbol{};
    FileStorage m_file;
//    TextUpDater upDater;
//    TextManager textManager;
};


#endif //VION_CHANGEAPPLIER_H
