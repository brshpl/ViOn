#include "Interpretator.h"
#include <fstream>
extern std::ofstream err;
Change Interpretator::Interpret(int &curChar, const Mode &mode,
                                const Position &position) {
    err << "Begin: Interpret" << std::endl;
    char c = static_cast<char>(curChar);
    std::string str;
    str.push_back(c);

//    buffer.push_back(c);
    err << "Begin: Interpret symbol:" << str << std::endl;
    Change change = changeCreator.CreateChange(mode, position, str);
    if (change.cmd != NOTHING) {
//        buffer.clear();
    }
    err << "End: Interpret" << std:: endl;
    return change;
}
