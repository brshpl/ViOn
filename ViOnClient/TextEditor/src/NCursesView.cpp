#include <ncurses.h>
#include "NCursesView.h"

#include "FileController/JsonParser.h"

#include <fstream>

std::ofstream err("ept");

[[noreturn]] void NCursesView::listen() {
    while (true) {
        noecho();
        int code = getch();
        Position pos(text_.getText().at(cursor.posY).at(cursor.posX).symbolId, 0);
        notify(code, pos);
    }
}

void NCursesView::notify(int symbol, Position next_symbol) {
    Change cur_change = interpretator_.Interpret(symbol, mode_, next_symbol);
    err << JsonParser::ParseToJson(cur_change) << std::endl;
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

void NCursesView::insertChar(const Change& ch) {
    client_.sendChanges(ch);
}

void NCursesView::deleteChar(const Change& ch) {
    client_.sendChanges(ch);
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
            insertChar(change);
            break;
        case DELETE_SYMBOL:
            deleteChar(change);
            break;
        default:
            break;
    }
}

void NCursesView::insertString() {
    cursor.posY++;
    cursor.posX = 0;
}

void NCursesView::show(const std::string &text) {
    View::show(text);
}
