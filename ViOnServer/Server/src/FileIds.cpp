#include <functional>
#include <ctime>

#include "FileIds.h"
#include <iostream>


FileIds::FileIds() {
    GenerateIds();
}

void FileIds::GenerateIds() {
    std::srand(std::time(nullptr)) ;
    file_ids_.clear();

    for (int i = 0; i < 10; ++i) {
        std::size_t id = 10000 + rand() % 90000;
        file_ids_.push_back(id);
    }
}

ssize_t FileIds::getFileId() {
    if (file_ids_.empty()) {
        return -1;
    }

    ssize_t id = file_ids_.back();
    file_ids_.pop_back();
    return id;
}
