//
// Created by Dashik on 12.11.2020.
//

#ifndef VION_TEXTMANAGER_H
#define VION_TEXTMANAGER_H
#include <iostream>
#include <vector>
#include "Parser.h"

struct Change{
    //пустая структура для тестов
};

struct SymbolState{
    char symbol;
    bool is_visible;
    std::size_t id;
};

struct StringState{
    std::vector<SymbolState> symbols;
    std::size_t id;
};

struct TextStorage{
    std::vector<StringState> strings;
    std::size_t file_id;
    std::size_t password;
};

class IDGenerator{
public:
    std::size_t getIdForChar();
    std::size_t getIdForString();
    static IDGenerator& Instance();
    static std::size_t charLastId;
    static std::size_t stringLastId;
private:
    IDGenerator();
    IDGenerator(IDGenerator const&) = delete;
    IDGenerator& operator= (IDGenerator const&) = delete;
    ~IDGenerator();
};


class TextManager {
public:
    static TextManager& Instance();
    struct TextStorage text;
    IDGenerator idGen;
private:
    TextManager();
    TextManager(TextManager const&) = delete;
    TextManager& operator= (TextManager const&) = delete;
    ~TextManager();
};

class TextManagerClient : public TextManager{
private:
    ParserState parser;
    TextManagerClient();
    ~TextManagerClient();
};

class TextManagerServer : public TextManager{
public:
    TextManagerServer();
    ~TextManagerServer();
    bool createFile();
    bool deleteFile();
    size_t createIdFile();
    size_t createPassword();
};

#endif //VION_TEXTMANAGER_H
