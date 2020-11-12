//
// Created by yakovitskiy on 12.11.2020.
//

#ifndef VION_MESSAGE_H
#define VION_MESSAGE_H

#include <string>

struct IMessage {};

struct Log : IMessage {
    size_t fileId;
    std::string info;
};

enum Command {
    CREATE_FILE,
    DELETE_FILE,
    INSERT_SUB_STRING,
    DELETE_STRING,
    DELETE_SYMBOL
};

struct Change : IMessage {
    enum Command cmd;
};

struct ChangeCreateFile : Change {
    Command cmd = CREATE_FILE;
};

struct ChangeDeleteFile : Change {
    Command cmd = DELETE_FILE;
    size_t fileId;
};

struct ChangeInsertSubString : Change {
    Command cmd = INSERT_SUB_STRING;
    size_t fileId;
    size_t stringId;
    size_t beginSymbolId;
    std::string subStr;
};

struct ChangeDeleteString : Change {
    Command cmd = DELETE_STRING;
    size_t fileId;
    size_t stringId;
};

struct ChangeDeleteSymbol : Change {
    Command cmd = DELETE_SYMBOL;
    size_t fileId;
    size_t stringId;
    size_t symbolId;
};

#endif  // VION_MESSAGE_H
