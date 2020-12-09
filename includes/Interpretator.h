
#ifndef INTERPRETATOR_H
#define INTERPRETATOR_H

#include <string>
#include "Message.h"
#include "Mode.h"
#include "Position.h"
#include "ChangeCreator.h"

class Interpretator {
public:
    Interpretator(): changeCreator(),
    buffer()
    {}

    Interpretator(const ChangeCreator& _changeCreator):
    changeCreator(_changeCreator),
    buffer()
    {}

    Change Interpret(char &curChar, Mode &mode,
                     Position &position);
private:
    ChangeCreator changeCreator;
    std::string buffer;
};

#endif //  INTERPRETATOR_H