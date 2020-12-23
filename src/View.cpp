// CLass must be implemented by user of the library using e.g. ncurses (by me before next RC)
#include <algorithm>
#include "View.h"

void View::moveCursor(Direction direction) {}

void View::listen(const int fd_in, const int fd_out) {}

void View::insertChar(char ch) {}

void View::deleteChar(char ch) {}

void View::show(const std::string &text) {}

std::string_view View::getStringFromText() {
    auto *str = new std::string;
    std::shared_ptr<std::string> strPtr(str);
    for(auto elem : text_) {
        strPtr->insert(strPtr->length(), 1, elem.symbol);
    }
    return strPtr;
}

void View::setText(Text &text) {
    text_ = text;
}
