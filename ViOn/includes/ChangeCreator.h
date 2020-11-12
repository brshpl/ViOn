//
// Created by yakovitskiy on 12.11.2020.
//

#ifndef VION_CHANGECREATOR_H
#define VION_CHANGECREATOR_H

#include "message.h"
#include "parser.h"
#include <vector>
#include <string>

class ChangeCreator {
public :
    ChangeCreator();
    Change CreateChange(char &curChar, Mode &mode,
                        Position &position, std::string &buffer);
    ~ChangeCreator();

private:
    std::vector<Parser> parsers;
};


#endif //VION_CHANGECREATOR_H
