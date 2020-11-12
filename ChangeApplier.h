//
// Created by Dashik on 12.11.2020.
//

#ifndef VION_CHANGEAPPLIER_H
#define VION_CHANGEAPPLIER_H
#include "TextManager.h"

class ChangeApplier {
public:
    ChangeApplier(Change ch);
    ChangeApplier(Change ch, IDGenerator idGen, TextManager manager);
    ~ChangeApplier();
    bool applyChanges();
    bool inputIdIntoChange();
    bool sendChange();

protected:
    Change ch;
    TextUpDater upDater;
    TextManager textManager;
};


#endif //VION_CHANGEAPPLIER_H
