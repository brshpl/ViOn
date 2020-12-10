#ifndef VIONTEXTEDITOR_VIEW_H
#define VIONTEXTEDITOR_VIEW_H

#include <string>
#include "Direction.h"
#include "Position.h"
#include "Text.h"
#include "TextEditor.h"

enum editorKey {
    ARROW_LEFT = 1000,
    ARROW_RIGHT,
    ARROW_UP,
    ARROW_DOWN,
    DEL_KEY,
    HOME_KEY,
    END_KEY,
    PAGE_UP,
    PAGE_DOWN
};

class View {
public:
    View();
    void moveCursor(Direction direction);

    TextEditor& getTextEditor();
    void listen(const int fd_in, const int fd_out);
private:
    void show(const std::string& text);
    static void disableRawMode();
    static void enableRawMode();
    void editorProcessKeypress(int fd);
    int editorReadKey(int fd);
    void editorRefreshScreen(int fd);
    void editorDrawRows(int fd);
    int getWindowSize(int *rows, int *cols);

    void editorMoveCursor(int key);

    static struct editorConfig {
        static int cx, cy;
        static int screenrows;
        static int screencols;
        static struct termios orig_termios;
    };

    TextEditor textEditor_;
    Text text_;
};


#endif //VIONTEXTEDITOR_VIEW_H
