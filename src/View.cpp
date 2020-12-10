//
// Created by brshpl on 12.11.2020.
//

#include <iostream>
#include <cstdlib>
#include <cstring>
#include <sys/ioctl.h>
#include <termios.h>
#include <unistd.h>
#include "View.h"

#define CTRL_KEY(k) ((k) & 0x1f)

void View::listen(const int fd_in, const int fd_out) {
    editorRefreshScreen(fd_out);
    editorProcessKeypress(fd_in);
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

    editorConfig::cx = 0;
    editorConfig::cy = 0;
    getWindowSize(&(editorConfig::screenrows), &(editorConfig::screencols));
}

void View::disableRawMode() {
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &(editorConfig::orig_termios));
}

void View::enableRawMode() {
    tcgetattr(STDIN_FILENO, &(editorConfig::orig_termios));
    atexit(disableRawMode);

    struct termios raw = editorConfig::orig_termios;
    raw.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
    raw.c_oflag &= ~(OPOST);
    raw.c_cflag |= (CS8);
    raw.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);
    raw.c_cc[VMIN] = 0;
    raw.c_cc[VTIME] = 1;

    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

int View::editorReadKey(int fd = 0) {
    char c;
    read(fd, &c, 1);

    if (c == '\x1b') {
        char seq[3];
        if (read(fd, &seq[0], 1) != 1) return '\x1b';
        if (read(fd, &seq[1], 1) != 1) return '\x1b';
        if (seq[0] == '[') {
            if (seq[1] >= '0' && seq[1] <= '9') {
                if (read(STDIN_FILENO, &seq[2], 1) != 1) return '\x1b';
                if (seq[2] == '~') {
                    switch (seq[1]) {
                        case '1': return HOME_KEY;
                        case '3': return DEL_KEY;
                        case '4': return END_KEY;
                        case '5': return PAGE_UP;
                        case '6': return PAGE_DOWN;
                        case '7': return HOME_KEY;
                        case '8': return END_KEY;
                    }
                }
            } else {
                switch (seq[1]) {
                    case 'A': return ARROW_UP;
                    case 'B': return ARROW_DOWN;
                    case 'C': return ARROW_RIGHT;
                    case 'D': return ARROW_LEFT;
                    case 'H': return HOME_KEY;
                    case 'F': return END_KEY;
                }
            }
        } else if (seq[0] == 'O') {
            switch (seq[1]) {
                case 'H': return HOME_KEY;
                case 'F': return END_KEY;
            }
        }
        }
        return '\x1b';
    } else {
        return c;
    }
}

void View::editorProcessKeypress(int fd = 0) {
    int c = editorReadKey();
    switch (c) {
        case CTRL_KEY('q'):
            exit(0);
            break;
        case ARROW_UP:
        case ARROW_DOWN:
        case ARROW_LEFT:
        case ARROW_RIGHT:
            editorMoveCursor(c);
            break;
    }
}

void View::editorRefreshScreen(int fd = 1) {
    write(fd, "\x1b[?25l", 6); // hide cursor
    write(fd, "\x1b[H", 3);

    editorDrawRows(fd);

    char buf[32];
    // move cursor to the stored position
    snprintf(buf, sizeof(buf), "\x1b[%d;%dH", editorConfig::cy + 1, editorConfig::cx + 1);
    write(fd, buf, strlen(buf));

    write(fd, "\x1b[?25h", 6); // show cursor
}

void View::editorDrawRows(int fd) {
    int y;
    // draws '~' at the begin of each line
    for (y = 0; y < editorConfig::screenrows; y++) {
        write(STDOUT_FILENO, "~", 1);
        write(fd, "\x1b[K", 3); // clear this line
        if (y < editorConfig::screenrows - 1) {
            write(STDOUT_FILENO, "\r\n", 2);
        }
    }
}

int View::getWindowSize(int *rows, int *cols) {
    struct winsize ws{};
    if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) == -1 || ws.ws_col == 0) {
        return -1;
    } else {
        *cols = ws.ws_col;
        *rows = ws.ws_row;
        return 0;
    }
}

void View::editorMoveCursor(int key) {
    switch (key) {
        case ARROW_LEFT:
            if (editorConfig::cx != 0) {
                editorConfig::cx--;
            }
            break;
        case ARROW_RIGHT:
            if (editorConfig::cx != editorConfig::screencols - 1) {
                editorConfig::cx++;
            }
            break;
        case ARROW_UP:
            if (editorConfig::cy != 0) {
                editorConfig::cy--;
            }
            break;
        case ARROW_DOWN:
            if (editorConfig::cy != editorConfig::screenrows - 1) {
                editorConfig::cy++;
            }
            break;
    }
}
