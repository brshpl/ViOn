#ifndef MESSAGE_H
#define MESSAGE_H

#include <string>
#include "Position.h"
#include <tuple>

enum Command {
    NOTHING,
    MOVE_UP,
    MOVE_DOWN,
    MOVE_RIGHT,
    MOVE_LEFT,
    CREATE_FILE,
    DELETE_FILE,
    INSERT_SUB_STRING,
    DELETE_STRING,
    DELETE_SYMBOL,
    CHANGE_MODE
};

struct Change {
    Change(): cmd(NOTHING), fileId(0), position({0, 0}), symbol(0)  {}
    Change(Command& _cmd, size_t& _fileId,
           Position& _position, char &_symbol):
           cmd(_cmd), fileId(_fileId), position(_position), symbol(_symbol) {}
    ~Change() = default;
    Command cmd;
    size_t fileId;
    Position position;
    char symbol;
};

#endif // MESSAGE_H
