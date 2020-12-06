#ifndef MESSAGE_H
#define MESSAGE_H

#include <string>
#include "Position.h"

enum Command {
    ERROR,
    CREATE_FILE,
    DELETE_FILE,
    INSERT_SUB_STRING,
    DELETE_STRING,
    DELETE_SYMBOL
};

struct Change {
    Command cmd;
    size_t fileId;
    Position position;
    std::string str;
};

#endif // MESSAGE_H