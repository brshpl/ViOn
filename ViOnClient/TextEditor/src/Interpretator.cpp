#include "TextEditor/Interpretator.h"
#include <fstream>
extern std::ofstream err;
Change Interpretator::Interpret(int &curChar, const Mode &mode,
                                const Position &position) {
    char c = static_cast<char>(curChar);
    std::string str;
    str.push_back(c);

//    buffer.push_back(c);
    Change change = changeCreator.CreateChange(mode, position, str);
    if (change.cmd != NOTHING) {
//        buffer.clear();
    }
    return change;
}
