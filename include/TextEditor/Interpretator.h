
#ifndef INTERPRETATOR_H
#define INTERPRETATOR_H

#include <string>
#include "Message.h"
#include "Mode.h"
#include "Position.h"
#include "ChangeCreator.h"

class Interpretator {
public:
    Interpretator(): changeCreator()
    {}

    explicit Interpretator(const ChangeCreator& _changeCreator):
            changeCreator(_changeCreator)
    {}

    Change Interpret(char &curChar, Mode &mode,
                     Position &position);
private:
    ChangeCreator changeCreator;
    static std::string buffer;
};

#endif //  INTERPRETATOR_H 