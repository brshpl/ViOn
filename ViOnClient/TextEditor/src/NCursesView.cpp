#include <ncurses.h>
#include "NCursesView.h"

#include "FileController/JsonParser.h"

#include <fstream>

std::ofstream err("ept");

[[noreturn]] void NCursesView::listen() {
    while (true) {
        curs_set(1);
        noecho();
        int code = getch();
        noecho();
        cursor.getYX();
        Position pos(text_.getText().at(cursor.posY).at(cursor.posX).symbolId, 0);
        switch (code) {
            case KEY_ENTER:
                text_.getText().emplace_back(1);
                notify(code, pos);
                break;
            case KEY_RIGHT:
                moveCursor(RIGHT);
                break;
            case KEY_LEFT:
                moveCursor(LEFT);
                break;
            case KEY_DOWN:
                moveCursor(DOWN);
                break;
            case KEY_UP:
                moveCursor(UP);
                break;
            default:
                notify(code, pos);
                break;
        }
    }
}

void NCursesView::notify(int symbol, Position next_symbol) {
    Change cur_change = interpretator_.Interpret(symbol, mode_, next_symbol);
    err << JsonParser::ParseToJson(cur_change) << std::endl;
    applyChange(cur_change);
}

void NCursesView::moveCursor(Direction direction) {
    cursor.getYX();
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
    cursor.getYX();
    text_.getText().at(cursor.posY).emplace_back();
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
    cursor.getYX();
    int y = cursor.posY;
    int x = cursor.posX;
    clear();
    int row, col;
    getmaxyx(stdscr, row, col);
    mvprintw(row - 1, 0, "File_id = ", fileId_);
    mvprintw(0, 0, "%s", text.data());
    move(y, x);
    refresh();
}
