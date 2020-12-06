#ifndef MESSAGE_H
#define MESSAGE_H

#include <string>
#include "Position.h"
#include <tuple>

enum Command {
    ERROR,
    CREATE_FILE,
    DELETE_FILE,
    INSERT_SUB_STRING,
    DELETE_STRING,
    DELETE_SYMBOL
};

struct Change {
    Change(): cmd(ERROR), fileId(0), position({0, 0}), str()  {}
    Change(Command& _cmd, size_t& _fileId,
           Position& _position, std::string& _str):
           cmd(_cmd), fileId(_fileId), position(_position), str(_str) {}
    ~Change() = default;
    Command cmd;
    size_t fileId;
    Position position;
    std::string str;
};

#endif // MESSAGE_H