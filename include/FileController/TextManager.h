//
// Created by Dashik on 12.11.2020.
//

#ifndef VION_TEXTMANAGER_H
#define VION_TEXTMANAGER_H
#include <iostream>
#include <vector>
#include "Parser.h"

enum Command{
    INSERT_SYMBOL,
    DELETE_SYMBOL
};
struct Change{
    Command cmd;
    size_t fileId;
    size_t symbolId;
    size_t stringId;
    size_t behind_symbol_id;
    char symbol;
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

//class IDGenerator{
//public:
//    std::size_t getIdForChar();
//    std::size_t getIdForString();
//    static IDGenerator& Instance();
//    static std::size_t charLastId;
//    static std::size_t stringLastId;
//private:
//    IDGenerator();
//    IDGenerator(IDGenerator const&) = delete;
//    IDGenerator& operator= (IDGenerator const&) = delete;
//    ~IDGenerator();
//};

struct FileStorage{
    std::vector<StringState> strings;
    size_t file_id;
    size_t password;
    size_t symbols_length;
    size_t strings_length;
//    IDGenerator idGenerator;
};

class TextManager {
public:
    static TextManager& Instance();
    struct FileStorage text;
//    IDGenerator idGen;
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

public:
    void listen(Client client);
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
