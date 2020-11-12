//
// Created by Dashik on 12.11.2020.
//

#ifndef VION_TEXTUPDATER_H
#define VION_TEXTUPDATER_H


class TextUpDater {
public:
    TextUpDater();
    ~TextUpDater();
    bool applyChanges();
    bool inputIdIntoChange();
    bool sendChange();

protected:
    Change ch;
    IDGenerator idGen;
};

class InsertChar : public TextUpDater{
public:
    InsertChar();
    ~InsertChar();
    char getSymbol();
    void insertSymbol();
};

class InsertString : public TextUpDater{
public:
    InsertString();
    ~InsertString();
    InsertChar char;
private:
    std::string getString();
    void insertString();
};

class DeleteChar : public TextUpDater{
public:
    DeleteChar();
    ~DeleteChar();
    char getSymbol();
    void deleteSymbol();
};

class DeleteString : public TextUpDater{
public:
    DeleteString();
    ~DeleteString();
    DeleteChar char;
private:
    std::string getString();
    void deleteString();
};


#endif //VION_TEXTUPDATER_H
