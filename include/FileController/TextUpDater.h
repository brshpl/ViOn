//
// Created by Dashik on 12.11.2020.
//

#ifndef VION_TEXTUPDATER_H
#define VION_TEXTUPDATER_H
#include <iostream>
#include "TextManager.h"

class TextUpDater {
public:
    TextUpDater(FileStorage file, Change ch);
    ~TextUpDater();
    bool applyChanges();
    bool inputIdIntoChange();
    bool sendChange();

protected:
    FileStorage m_file;
    Change m_ch;
//    IDGenerator idGen;
};

class InsertChar : public TextUpDater{
public:
    explicit InsertChar(FileStorage file, Change ch);
    ~InsertChar();
private:
    Change add_new_id();
    void insertSymbol();
    char getSymbol();
};

class InsertString : public TextUpDater{
public:
    explicit InsertString();
    ~InsertString();
    InsertChar symbol;
private:
    std::string getString();
    void insertString();
};

class DeleteChar : public TextUpDater{
public:
    explicit DeleteChar(FileStorage file, Change ch);
    ~DeleteChar();
private:
    char getSymbol();
    void deleteSymbol();
};

class DeleteString : public TextUpDater{
public:
    DeleteString();
    ~DeleteString();
    DeleteChar symbol;
private:
    std::string getString();
    void deleteString();
};


#endif //VION_TEXTUPDATER_H
