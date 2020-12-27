#ifndef VION_FILESTORAGE_H
#define VION_FILESTORAGE_H

#include <iostream>
#include <list>
#include <vector>
#include "Message.h"
#include "Position.h"


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
