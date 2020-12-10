//
// Created by Dashik on 12.11.2020.
//

#include "FileController/TextManager.h"
FileStorage::FileStorage(size_t file_id) {
    SymbolState symbol = {'\0', true, 0};
    symbols.push_back(symbol);
    symbols_length = 0;
    file_id = file_id;
}
