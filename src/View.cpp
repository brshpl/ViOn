// CLass must be implemented by user of the library using e.g. ncurses (by me before next RC)
#include <algorithm>
#include "View.h"

void View::moveCursor(Direction direction) {}

void View::listen(const int fd_in, const int fd_out) {}

void View::insertChar(char ch) {}

void View::deleteChar(char ch) {}

void View::show(const std::string &text) {}

std::string_view& View::getStringFromText() {
    std::string str;
    std::vector<Symbol> text = text_.getText();
    for(auto elem : text) {
        str += elem.symbol;
    }
    static std::string_view result(str);
    return result;
}

void View::setText(Text &text) {
    text_ = text;
}
