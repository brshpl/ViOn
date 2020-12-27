#include "FileController/FileStorage.h"


FileStorage::FileStorage(size_t file_id)
    : symbols_length(0), file_id(file_id) {
    SymbolState symbol = {'\0', true, 0};
    symbols.emplace_back(symbol);
}