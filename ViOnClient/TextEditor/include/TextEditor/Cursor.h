#ifndef VION_NCURSES_CURSOR_H
#define VION_NCURSES_CURSOR_H

#include "Direction.h"
#include "Text.h"

struct Cursor {
    size_t posY = 0;
    size_t posX = 0;
    void getYX();
};


#endif //VION_NCURSES_CURSOR_H
