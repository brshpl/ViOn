//
// Created by Dashik on 12.11.2020.
//

#ifndef VION_TEXTMANAGER_H
#define VION_TEXTMANAGER_H
#include <iostream>
#include <vector>

//Структура для передачи данных (потом удалить)
enum Command{
    ERROR,
    INSERT_SYMBOL,
    DELETE_SYMBOL,
    CREATE_FILE,
    CLOSE_CONNECT,
    CONNECT_TO_FILE
};

struct Position {
//    Position(): stringId(0), symbolId(0) {}
//    Position(size_t _stringId, size_t _symbolId):
//            stringId(_stringId), symbolId(_symbolId) {}
    Position(): symbolId(0) {}
    Position(size_t _symbolId):
            symbolId(_symbolId) {}
    ~Position() = default;
//    size_t  stringId;
    size_t symbolId;
};

struct Change{
    Change(): cmd(ERROR), fileId(0), position(0),
              newSymbolId(), symbol() {}
    Change(Command _cmd, size_t _fileId,
           Position& _position, size_t _newSymbolId, char _symbol):
            cmd(_cmd), fileId(_fileId), position(_position),
            newSymbolId(_newSymbolId), symbol(_symbol) {}
    ~Change() = default;
    Command cmd;
    size_t fileId;
    Position position;
    size_t newSymbolId;
    char symbol;
};

//Структуры для хранения файла
struct SymbolState{
    char symbol;
    bool is_visible;
    size_t id;
};

//Для дальнейшего развития системы
//struct StringState{
//    std::vector<SymbolState> symbols;
//    std::size_t id;
//};

struct FileStorage{
    FileStorage(): symbols(0), symbols_length(0), file_id(0) {}
    explicit FileStorage(size_t file_id);
    std::vector<SymbolState> symbols;
    size_t symbols_length;
    size_t file_id;
//    size_t strings_length;
};


#endif //VION_TEXTMANAGER_H
