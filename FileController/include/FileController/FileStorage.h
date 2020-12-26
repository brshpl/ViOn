#ifndef VION_FILESTORAGE_H
#define VION_FILESTORAGE_H

#include <iostream>
#include <list>
#include <vector>

///--------
enum Command{
    ERROR,
    INSERT_SYMBOL,
    DELETE_SYMBOL,
    CREATE_FILE,
    CLOSE_CONNECT,
    CONNECT_TO_FILE,
    NO_SUCH_FILE_ID,
};

struct Position {
    Position(): symbolId(0) {}
    Position(size_t _symbolId):
            symbolId(_symbolId) {}
    ~Position() = default;
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
///--------


struct SymbolState{
    SymbolState(char symbol, bool is_visible, size_t id) : symbol(symbol), is_visible(is_visible), id(id) {}
    char symbol;
    bool is_visible;
    size_t id;
};

struct FileStorage{
    explicit FileStorage(size_t file_id = 0);
    std::list<SymbolState> symbols;
    size_t symbols_length;
    size_t file_id;
};

struct Symbol{
    char symbol;
    size_t symbol_id;
};

#endif  // VION_FILESTORAGE_H
