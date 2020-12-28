#include "Cursor.h"
#include "ncurses.h"


void Cursor::getYX() {
    getyx(stdscr, posY, posX);
}
