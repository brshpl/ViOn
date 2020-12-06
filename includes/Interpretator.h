
#ifndef INTERPRETATOR_H
#define INTERPRETATOR_H

#include <string>
#include <vector>
#include "Message.h"
#include "Mode.h"
#include "Position.h"
#include "Parser.h"

class Interpretator {
public:
    Interpretator();
    Change Interpret(const char &curChar, Mode mode,
                     Position &position);
private :
    Parser changeCreator;
    std::string buffer;
};

#endif //  INTERPRETATOR_H