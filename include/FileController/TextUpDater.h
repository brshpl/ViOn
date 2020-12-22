//
// Created by Dashik on 12.11.2020.
//

#ifndef VION_TEXTUPDATER_H
#define VION_TEXTUPDATER_H
#include <iostream>
#include <memory>
#include "TextManager.h"

class TextUpDater {
public:
    TextUpDater()= default;
    TextUpDater(const std::shared_ptr<FileStorage>& file, Change ch);
    ~TextUpDater()= default;
    Change getChange();
    FileStorage getFile();

protected:
    std::shared_ptr<FileStorage> file_;
    Change ch_;
};

class InsertChar : public TextUpDater{
public:
    explicit InsertChar(const std::shared_ptr<FileStorage>& file, Change &ch);
    bool insertSymbol();
    ~InsertChar()= default;;
private:
    Change addNewId();
};

class DeleteChar : public TextUpDater{
public:
    explicit DeleteChar(const std::shared_ptr<FileStorage>& file, Change ch);
    ~DeleteChar()= default;;
    bool deleteSymbol();
};

class InsertString : public TextUpDater{
public:
    explicit InsertString();
    ~InsertString(){};
    InsertChar symbol;
private:
    std::string getString();
    void insertString();
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
