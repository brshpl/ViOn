//
// Created by Dashik on 12.11.2020.
//

#ifndef VION_TEXTMANAGER_H
#define VION_TEXTMANAGER_H

struct SymbolState{
    char symbol;
    bool is_visible;
    size_t id;
};

struct StringState{
    std::vector<SymbolState> symbols;
    size_t id;
};

struct TextStorage{
    std::vector<StringState> strings;
    size_t file_id;
    size_t password;
};

class IDGenerator{
public:
    size_t getIdForChar();
    size_t getIdForString();
    static IDGenerator& Instance();
    static size_t charLastId;
    static size_t stringLastId;
private:
    IDGenerator();
    IDGenerator(IDGenerator const&) = delete;
    IDGenerator& operator= (IDGenerator const&) = delete;
    ~IDGenerator();
};


class TextManager {
public:
    static TextManager& Instance();
    struct TextStorage;
    IDGenerator idGen;
private:
    TextManager();
    TextManager(TextManager const&) = delete;
    TextManager& operator= (TextManager const&) = delete;
    ~TextManager();
};

class TextManagerClient : public TextManager{
private:
    ParseState parser;
    TextManagerClient();
    ~TextManagerClient();
    TextStorage parseText();
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
