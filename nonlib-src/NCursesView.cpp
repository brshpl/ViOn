//
// Created by brshpl on 24.12.2020.
//

#include "NCursesView.h"
#include <ncurses.h>

void NCursesView::listen_test() {
    while (true) {
        noecho();
        int code = getch();
        while (text_.getText().size() < cursor.posY)
            text_.getText().emplace_back();
        while (text_.getText().at(cursor.posY).size() < cursor.posX)
            text_.getText().at(cursor.posY).emplace_back();
        if (code != KEY_ENTER)
            insertChar(code);
        else
            insertString();
    }
}

[[noreturn]] void NCursesView::listen() {
    while (true) {
        noecho();
        int code = getch();
        notify(code, Position(text_.getText().at(cursor.posY).at(cursor.posX).symbolId, 0));
    }
}

void NCursesView::notify(int symbol, Position next_symbol) {
    Change cur_change = interpretator_.Interpret(symbol, mode_, next_symbol);
    applyChange(cur_change);
}

void NCursesView::moveCursor(Direction direction) {
    switch (direction) {
        case LEFT:
            if (cursor.posX > 0)
                move(cursor.posY , --cursor.posX);
            else if (cursor.posY > 0) {
                cursor.posX = text_.getText().at(--cursor.posY).size();
                move(cursor.posY, cursor.posX);
            }
            break;
        case RIGHT:
            if (cursor.posX < text_.getText().at(cursor.posY).size() - 1)
                move(cursor.posY, ++cursor.posX);
            else if (cursor.posY < text_.getText().size() - 1) {
                cursor.posX = 0;
                move(++cursor.posY, cursor.posX);
            }
            break;
        case UP:
            if (cursor.posY > 0) {
                if (cursor.posX <= text_.getText().at(--cursor.posY).size() - 1) {
                    move(cursor.posY, cursor.posX);
                } else {
                    cursor.posX = text_.getText().at(cursor.posY).size();
                    move(cursor.posY, cursor.posX);
                }
            }
            break;
        case DOWN:
            if (cursor.posY < text_.getText().size() - 1) {
                if (cursor.posX <= text_.getText().at(++cursor.posY).size() - 1) {
                    move(cursor.posY, cursor.posX);
                } else {
                    cursor.posX = text_.getText().at(cursor.posY).size();
                    move(cursor.posY, cursor.posX);
                }
            }
            break;
        default:
            break;
    }
}

void NCursesView::insertChar(char ch) {
    mvaddch(cursor.posY, cursor.posX++, ch);
}

void NCursesView::deleteChar(char ch) {

}

void NCursesView::applyChange(const Change &change) {
    switch (change.cmd) {
        case NOTHING:
            break;
        case MOVE_UP:
            moveCursor(UP);
            break;
        case MOVE_DOWN:
            moveCursor(DOWN);
            break;
        case MOVE_RIGHT:
            moveCursor(RIGHT);
            break;
        case MOVE_LEFT:
            moveCursor(LEFT);
            break;
        case CHANGE_MODE: {
            Mode newMode = (mode_ == COMMAND_MODE) ? INSERTATION_MODE : COMMAND_MODE;
            changeMode(newMode);
            break;
        }
        case INSERT_SYMBOL:
            insertChar(change.symbol);
            break;
        case DELETE_SYMBOL:
            deleteChar(change.symbol);
            break;
        default:
            break;
    }
}

void NCursesView::insertString() {
    cursor.posY++;
    cursor.posX = 0;
}
