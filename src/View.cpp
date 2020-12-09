//
// Created by brshpl on 12.11.2020.
//

#include <iostream>
#include <cstdlib>
#include <termios.h>
#include <unistd.h>
#include "View.h"

#define CTRL_KEY(k) ((k) & 0x1f)

void View::listen(const int fd) {
    // TODO: add implementation for listen to the file descriptor
    while (true) {
        char c = '\0';
        read(STDIN_FILENO, &c, 1);
        if (iscntrl(c)) {
            printf("%d\r\n", c);
        } else {
            printf("%d ('%c')\r\n", c, c);
        }
        if (c == CTRL_KEY('q')) break;
    }
}

void View::show(const std::string& text) {

}

void View::moveCursor(Direction direction) {

}

TextEditor &View::getTextEditor() {
    return textEditor_;
}

View::View() {
    enableRawMode();
}

void View::disableRawMode() {
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);
}

void View::enableRawMode() {
    tcgetattr(STDIN_FILENO, &orig_termios);
    atexit(disableRawMode);

    struct termios raw = orig_termios;
    raw.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
    raw.c_oflag &= ~(OPOST);
    raw.c_cflag |= (CS8);
    raw.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);
    raw.c_cc[VMIN] = 0;
    raw.c_cc[VTIME] = 1;

    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}
