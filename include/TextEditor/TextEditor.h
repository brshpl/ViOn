#ifndef VIONTEXTEDITOR_TEXTEDITOR_H
#define VIONTEXTEDITOR_TEXTEDITOR_H

#include "Listener.h"
#include "View.h"
#include "TextStorage.h"

enum Mode { INSERT, COMMAND };

class TextEditor {
public:
    TextEditor();
    void run();
    void update();
private:
    void changeMode();
    void editText();
    Mode mode;
    Listener listener;
    View view;
    TextStorage text;
};


#endif //VIONTEXTEDITOR_TEXTEDITOR_H
