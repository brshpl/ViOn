#pragma once

#include <list>

struct SymbolState{
    SymbolState(char symbol, bool is_visible, size_t id) : symbol(symbol), is_visible(is_visible), id(id) {}
    char symbol;
    bool is_visible;
    size_t id;
};

struct FileStorage{
    explicit FileStorage(size_t file_id): symbols_length(0), file_id(file_id) {
        SymbolState symbol = {'\0', true, 0};
        symbols.emplace_back(symbol);
    };

    std::list<SymbolState> symbols;
    size_t symbols_length;
    size_t file_id;
};

struct Symbol{
    char symbol;
    size_t symbol_id;
};
