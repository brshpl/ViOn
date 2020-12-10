// CLass must be implemented by user of the library using e.g. ncurses
#include <View.h>

void View::setText(std::vector<Symbol> &text) {
    text_ = text;
}

void View::moveCursor(Direction direction) {}

void View::listen(const int fd_in, const int fd_out) {}

void View::insertChar(char ch) {}

void View::deleteChar(char ch) {}

void View::show(const std::string &text) {}
