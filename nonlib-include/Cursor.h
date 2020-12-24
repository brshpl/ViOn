//
// Created by brshpl on 24.12.2020.
//

#ifndef VION_NCURSES_CURSOR_H
#define VION_NCURSES_CURSOR_H

#include "Direction.h"
#include "Text.h"

struct Cursor {
    size_t posY = 0;
    size_t posX = 0;
    void getYX(int& y, int& x) const;
};


#endif //VION_NCURSES_CURSOR_H
