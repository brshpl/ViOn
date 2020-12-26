#include "ChangeCreator.hpp"
#include <iostream>


void ChangeCreator::AddChangeCreator(ChangeCreator* _changeCreator) {
    changeCreators.push_back(_changeCreator);
}

bool ChangeCreator::CanCreate(const Mode &mode,
                              const Position &position, const std::string_view &buffer) {
    for (auto creator: changeCreators) {
        if (creator->CanCreate(mode, position, buffer)) {
            return true;
        }
    }
    return false;
}

Change ChangeCreator::CreateChange(const Mode &mode,
                                   const Position &position, const std::string_view &buffer) {
    for (auto creator: changeCreators) {
        if (creator->CanCreate(mode, position, buffer)) {
            return creator->CreateChange(mode, position, buffer);
        }
    }
    Change chg;
    return chg;
}

bool ChangeCreatorInsertSubString::CanCreate(const Mode &mode,
                                             const Position &position, const std::string_view &buffer) {
    char curChar  = buffer.back();
    if (mode == INSERTATION_MODE && !(curChar == 127 || curChar == 8)) {
        return true;
    } else {
        return false;
    }
}

Change ChangeCreatorInsertSubString::CreateChange(const Mode &mode,
                                                  const Position &position, const std::string_view &buffer) {
    Change chg;
    chg.cmd = INSERT_SYMBOL;
    chg.fileId = 0;
    chg.position = position;
    chg.symbol = buffer.back();
    return chg;
}

bool ChangeCreatorDeleteSymbol::CanCreate(const Mode &mode,
                                          const Position &position, const std::string_view &buffer) {
    char curChar  = buffer.back();
    if (mode == INSERTATION_MODE && (curChar == 127 || curChar == 8)) {
        return true;
    }
    else {
        return false;
    }
}

Change ChangeCreatorDeleteSymbol::CreateChange(const Mode &mode,
                                               const Position &position, const std::string_view &buffer) {
    Change chg;
    chg.cmd = DELETE_SYMBOL;
    chg.fileId = 0;
    chg.position = position;
    return chg;
}

bool ChangeCreatorDeleteString::CanCreate(const Mode &mode,
                                          const Position &position, const std::string_view &buffer) {
    if (mode == COMMAND_MODE && buffer == "dd") {
        return true;
    }
    else {
        return false;
    }
}

Change ChangeCreatorDeleteString::CreateChange(const Mode &mode,
                                               const Position &position, const std::string_view &buffer) {
    Change chg;
    chg.cmd = DELETE_STRING;
    chg.fileId = 0;
    chg.position = position;
    return chg;
}

bool ChangeCreatorCreateFile::CanCreate(const Mode &mode,
                                        const Position &position, const std::string_view &buffer) {
    if (mode == COMMAND_MODE && buffer == "CREATE_FILE") {
        return true;
    } else {
        return false;
    }
}

Change ChangeCreatorCreateFile::CreateChange(const Mode &mode,
                                             const Position &position, const std::string_view &buffer) {
    Change chg;
    chg.cmd = CREATE_FILE;
    chg.position = {0, 0};
    chg.fileId = 0;
    return chg;
}

bool ChangeCreatorDeleteFile::CanCreate(const Mode &mode,
                                        const Position &position, const std::string_view &buffer) {
    if (mode == COMMAND_MODE && buffer == "DELETE_FILE") {
        return true;
    } else {
        return false;
    }
}

Change ChangeCreatorDeleteFile::CreateChange(const Mode &mode,
                                             const Position &position, const std::string_view &buffer) {
    Change chg;
    chg.cmd = DELETE_FILE;
    chg.position = {0, 0};
    chg.fileId = 0;
    return chg;
}

bool ChangeCreatorMoveCursor::CanCreate(const Mode &mode,
                                        const Position &position, const std::string_view &buffer) {
    if (buffer[buffer.size() - 3] == 27
    && buffer[buffer.size() - 2] == 91
    && (buffer.back() >= 65 && buffer.back() <= 68)) {
        return true;
    }
    return false;
}

Change ChangeCreatorMoveCursor::CreateChange(const Mode &mode,
                                             const Position &position, const std::string_view &buffer) {
    Change chg;
    chg.position = position;
    switch (buffer.back()) {
        case 'A':
            chg.cmd = MOVE_UP;
            break;
        case 'B':
            chg.cmd = MOVE_DOWN;
            break;
        case 'C':
            chg.cmd = MOVE_RIGHT;
            break;
        case 'D':
            chg.cmd = MOVE_LEFT;
            break;
    }
    return chg;
}

