// CLass must be implemented by user of the library using e.g. ncurses (by me before next RC)
#include <algorithm>
#include <ncurses.h>
#include "TextEditor/View.h"

void View::moveCursor(Direction direction) {}

void View::listen(const int fd_in, const int fd_out) {}

void View::insertChar(char ch) {}

void View::deleteChar(char ch) {}

void View::show(const std::string &text) {}

std::string_view View::getStringFromText() {
    std::string str;
    std::vector<std::vector<Symbol>> text = text_.getText();
    for(const auto& string : text) {
        for (auto elem : string)
            str += elem.symbol;
    }
    return std::string_view {str};
}

void View::setText(Text &text) {
    text_ = text;
}

void View::notify(int symbol, Position next_symbol) {
    Change cur_change = interpretator_.Interpret(symbol, mode_, next_symbol);
    applyChange(cur_change);
}

void View::changeMode(Mode newMode) {
    mode_ = newMode;
}
Mode View::getMode() {
    return mode_;
}

void View::applyChange(const Change &change) {
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