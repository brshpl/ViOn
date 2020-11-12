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
};

class TextManager {
public:
    static TextManager& Instance();
    bool createFile();
    bool deleteFile();
    struct TextStorage getText();
    struct TextStorage;
private:
    TextManager();
    TextManager(TextManager const&) = delete;
    TextManager& operator= (TextManager const&) = delete;
    ~TextManager();
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

#endif //VION_TEXTMANAGER_H
