// CLass must be implemented by user of the library using e.g. ncurses (by me before next RC)
#include <algorithm>
#include "View.h"

void View::setText(std::vector<Symbol> &text) {
    text_ = text;
}

void View::moveCursor(Direction direction) {}

void View::listen(const int fd_in, const int fd_out) {}

void View::insertChar(char ch) {}

void View::deleteChar(char ch) {}

void View::show(const std::string &text) {}

std::shared_ptr<std::string> View::getStringFromText() {
    std::shared_ptr<std::string> str;
    auto it = text_.begin();
    for_each(it, text_.end(), str->insert(str->length(), reinterpret_cast<const char *>(it->symbol)));
    return str;
}
