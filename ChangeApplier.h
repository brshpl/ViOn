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
    IDGenerator idGen;
    TextManager manager
};

class InsertChar : public ChangeApplier{
public:
    InsertChar();
    ~InsertChar();
    char getSymbol();
    void insertSymbol();
};

class InsertString : public ChangeApplier{
public:
    InsertString();
    ~InsertString();
    InsertChar char;
private:
    std::string getString();
    void insertString();
};

class DeleteChar{
public:
    DeleteChar();
    ~DeleteChar();
    char getSymbol();
    void deleteSymbol();
};

class DeleteString{
public:
    DeleteString();
    ~DeleteString();
    DeleteChar char;
private:
    std::string getString();
    void deleteString();

};



#endif //VION_CHANGEAPPLIER_H
