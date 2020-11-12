//
// Created by yakovitskiy on 12.11.2020.
//

#ifndef VION_INTERPRETATOR_H
#define VION_INTERPRETATOR_H

#include <string>
#include "message.h"
#include "ChangeCreator.h"

struct Position {
    size_t  stringId;
    size_t symbolId;
};

enum Mode {
    INSERTATION_MODE,
    COMMAND_MODE
};

class Interpretator {
public :
    Interpretator();
    Change Interpret(const char &curChar, Mode mode,
                     Position &position);
private :
    ChangeCreator changeCreator;
    std::string buffer;
};

#endif //VION_INTERPRETATOR_H
