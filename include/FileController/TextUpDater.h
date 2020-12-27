#pragma once

#include "Message.h"
#include "FileStorage.h"

class TextUpDater {
public:
    TextUpDater() = default;
    TextUpDater(FileStorage* file_, Change ch);
    ~TextUpDater() = default;
    Change getChange();
    FileStorage getFile();

protected:
    FileStorage* file_ {};
    Change ch_;
};

class InsertChar : public TextUpDater {
public:
    InsertChar() = default;
    explicit InsertChar(FileStorage* file, Change &ch);
    bool insertSymbol();
    ~InsertChar() = default;;
private:
    Change addNewId();
};

class DeleteChar : public TextUpDater {
public:
    explicit DeleteChar(FileStorage* file, Change ch);
    DeleteChar() = default;
    ~DeleteChar() = default;;
    bool deleteSymbol();
};
