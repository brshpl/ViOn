#include <memory>
#include <string>
#include <vector>
#include "Direction.h"
#include "Symbol.h"

class View {
public:
    void moveCursor(Direction direction);
    void listen(int fd_in, int fd_out);
    void insertChar(char ch);
    void deleteChar(char ch);
    void setText(std::vector<Symbol> &text);
    std::shared_ptr<std::string> getStringFromText();
private:

    std::vector<Symbol> text_;
    void show(const std::string& text);
};





































































































//#ifndef VIONTEXTEDITOR_VIEW_H
//#define VIONTEXTEDITOR_VIEW_H
//
//#include <string>
//#include "Direction.h"
//#include "Position.h"
//#include "Symbol.h"
//#include "TextEditor.h"
//
//enum editorKey {
//    ARROW_LEFT = 1000,
//    ARROW_RIGHT,
//    ARROW_UP,
//    ARROW_DOWN,
//    DEL_KEY,
//    HOME_KEY,
//    END_KEY,
//    PAGE_UP,
//    PAGE_DOWN
//};
//
//class View {
//public:
//    View();
//    void moveCursor(Direction direction);
//
//    TextEditor& getTextEditor();
//    void listen(const int fd_in, const int fd_out);
//private:
//    void show(const std::string& text);
//    static void disableRawMode();
//    static void enableRawMode();
//    void editorProcessKeypress(int fd);
//    int editorReadKey(int fd);
//    void editorRefreshScreen(int fd);
//    void editorDrawRows(int fd);
//    int getWindowSize(int *rows, int *cols);
//
//    void editorMoveCursor(int key);
//
//    static struct editorConfig {
//        static int cx, cy;
//        static int screenrows;
//        static int screencols;
//        static struct termios orig_termios;
//    };
//
//    TextEditor textEditor_;
//    Symbol text_;
//};
//
//
//#endif //VIONTEXTEDITOR_VIEW_H
