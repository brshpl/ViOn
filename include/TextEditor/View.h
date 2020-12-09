#ifndef VIONTEXTEDITOR_VIEW_H
#define VIONTEXTEDITOR_VIEW_H

#include <string>
#include "Direction.h"
#include "Position.h"
#include "Text.h"
#include "TextEditor.h"

class View {
public:
    View();
    void moveCursor(Direction direction);

    TextEditor& getTextEditor();
    void listen(int fd);
private:
    void show(const std::string& text);
    static void disableRawMode();
    static void enableRawMode();

    static struct termios orig_termios;
    TextEditor textEditor_;
    Text text_;
};


#endif //VIONTEXTEDITOR_VIEW_H
