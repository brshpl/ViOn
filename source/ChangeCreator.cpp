#include "ChangeCreator.h"
#include <iostream>


void ChangeCreator::AddChangeCreator(ChangeCreator* _changeCreator) {
    changeCreators.push_back(_changeCreator);
}

bool ChangeCreator::CanCreate(Mode &mode,
                              Position &position, std::string &buffer) {
    for (auto creator: changeCreators) {
        if (creator->CanCreate(mode, position, buffer)) {
            return true;
        }
    }
    return false;
}

Change ChangeCreator::CreateChange(Mode &mode,
                                   Position &position, std::string &buffer) {
    try {
        for (auto creator: changeCreators) {
            if (creator->CanCreate(mode, position, buffer)) {
                return creator->CreateChange(mode, position, buffer);
            }
        }
        throw "Can't parse this data\n";
    }
    catch (const char* msg) {
        std::cout << msg << std::endl;
        Change chg;
        chg.cmd = NOTHING;
        return chg;
    }
}

bool ChangeCreatorInsertSubString::CanCreate(Mode &mode,
                                             Position &position, std::string &buffer) {
    char curChar  = buffer.back();
    if (mode == INSERTATION_MODE && !(curChar == 127 || curChar == 8)) {
        return true;
    } else {
        return false;
    }
}

Change ChangeCreatorInsertSubString::CreateChange(Mode &mode,
                                                  Position &position, std::string &buffer) {
    Change chg;
    chg.cmd = INSERT_SUB_STRING;
    chg.position = position;
    chg.symbol = buffer.back();
    return chg;
}

bool ChangeCreatorDeleteSymbol::CanCreate(Mode &mode,
                                          Position &position, std::string &buffer) {
    char curChar  = buffer.back();
    if (mode == INSERTATION_MODE && (curChar == 127 || curChar == 8)) {
        return true;
    }
    else {
        return false;
    }
}

Change ChangeCreatorDeleteSymbol::CreateChange(Mode &mode,
                                               Position &position, std::string &buffer) {
    Change chg;
    chg.cmd = DELETE_SYMBOL;
    chg.position = position;
    return chg;
}

bool ChangeCreatorDeleteString::CanCreate(Mode &mode,
                                          Position &position, std::string &buffer) {
    if (mode == COMMAND_MODE && buffer == "dd") {
        return true;
    }
    else {
        return false;
    }
}

Change ChangeCreatorDeleteString::CreateChange(Mode &mode,
                                               Position &position, std::string &buffer) {
    Change chg;
    chg.cmd = DELETE_STRING;
    chg.position = position;
    return chg;
}

bool ChangeCreatorCreateFile::CanCreate(Mode &mode,
                                        Position &position, std::string &buffer) {
    if (mode == COMMAND_MODE && buffer == "CREATE_FILE") {
        return true;
    } else {
        return false;
    }
}

Change ChangeCreatorCreateFile::CreateChange(Mode &mode,
                                             Position &position, std::string &buffer) {
    Change chg;
    chg.cmd = CREATE_FILE;
    return chg;
}

bool ChangeCreatorDeleteFile::CanCreate(Mode &mode,
                                        Position &position, std::string &buffer) {
    if (mode == COMMAND_MODE && buffer == "DELETE_FILE") {
        return true;
    } else {
        return false;
    }
}

Change ChangeCreatorDeleteFile::CreateChange(Mode &mode,
                                             Position &position, std::string &buffer) {
    Change chg;
    chg.cmd = DELETE_FILE;
    return chg;
}

bool ChangeCreatorChangeMode::CanCreate(Mode &mode,
                                        Position &position, std::string &buffer) {
    if ((mode == COMMAND_MODE && buffer == "I")
    || (mode == INSERTATION_MODE && buffer.back() == 27)) {
        return true;
    } else {
        return false;
    }
}

Change ChangeCreatorChangeMode::CreateChange(Mode &mode,
                                             Position &position, std::string &buffer) {
    Change chg;
    chg.cmd = CHANGE_MODE;
    return chg;
}
