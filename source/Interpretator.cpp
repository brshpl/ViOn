#include "Interpretator.h"

Change Interpretator::Interpret(char &curChar, Mode &mode, Position &position) {
    buffer += curChar;
    Change change = changeCreator.CreateChange(mode, position, buffer);
    if (change.cmd != NOTHING) {
        buffer.clear();
    }
    return change;
}
