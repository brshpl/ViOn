#include "Parser.h"
#include <iostream>


void Parser::AddParser(Parser* _parser) {
    parsers.push_back(_parser);
}

bool Parser::CanParse(char &curChar, Mode &mode, Position &position, std::string &buffer) {
    for (auto parser: parsers) {
        if (parser->CanParse(curChar, mode, position, buffer)) {
            return true;
        }
    }
    return false;
}

Change Parser::Parse(char &curChar, Mode &mode, Position &position, std::string &buffer) {
    try {
        for (auto parser: parsers) {
            if (parser->CanParse(curChar, mode, position, buffer)) {
                return parser->Parse(curChar, mode, position, buffer);
            }
        }
        throw "Can't parse this data\n";
    }
    catch (const char* msg) {
        std::cout << msg << std::endl;
        Change chg;
        chg.cmd = ERROR;
        chg.str = msg;
        return chg;
    }
}

bool ParseInsertSubString::CanParse(char &curChar, Mode &mode, Position &position, std::string &buffer) {
    if (mode == INSERTATION_MODE && !(curChar == 127 || curChar == 8)) {
        return true;
    } else {
        return false;
    }
}

Change ParseInsertSubString::Parse(char &curChar, Mode &mode, Position &position, std::string &buffer) {
    Change chg;
    chg.cmd = INSERT_SUB_STRING;
    chg.fileId = 0;
    chg.position = position;
    chg.str = curChar + buffer;
    return chg;
}

bool ParserDeleteSymbol::CanParse(char &curChar, Mode &mode, Position &position, std::string &buffer) {
    if (mode == INSERTATION_MODE && (curChar == 127 || curChar == 8)) {
        return true;
    }
    else {
        return false;
    }
}

Change ParserDeleteSymbol::Parse(char &curChar, Mode &mode, Position &position, std::string &buffer) {
    Change chg;
    chg.cmd = DELETE_SYMBOL;
    chg.fileId = 0;
    chg.position = position;
    chg.str = "";
    return chg;
}

bool ParserDeleteString::CanParse(char &curChar, Mode &mode, Position &position, std::string &buffer) {
    if (mode == COMMAND_MODE && buffer == "dd") {
        return true;
    }
    else {
        return false;
    }
}

Change ParserDeleteString::Parse(char &curChar, Mode &mode, Position &position, std::string &buffer) {
    Change chg;
    chg.cmd = DELETE_STRING;
    chg.fileId = 0;
    chg.position = position;
    chg.str = "";
    return chg;
}

bool ParserCreateFile::CanParse(char &curChar, Mode &mode, Position &position, std::string &buffer) {
    if (mode == COMMAND_MODE
    && position.symbolId == 0
    && position.stringId == 0
    && buffer == "CREATE_FILE") {
        return true;
    } else {
        return false;
    }
}

Change ParserCreateFile::Parse(char &curChar, Mode &mode, Position &position, std::string &buffer) {
    Change chg;
    chg.cmd = CREATE_FILE;
    chg.position = {0, 0};
    chg.fileId = 0;
    chg.str = "";
    return chg;
}

bool ParserDeleteFile::CanParse(char &curChar, Mode &mode, Position &position, std::string &buffer) {
    if (mode == COMMAND_MODE
    && position.symbolId == 0
    && position.stringId == 0
    && buffer == "DELETE_FILE") {
        return true;
    } else {
        return false;
    }
}
