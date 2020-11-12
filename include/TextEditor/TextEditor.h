#ifndef VIONTEXTEDITOR_TEXTEDITOR_H
#define VIONTEXTEDITOR_TEXTEDITOR_H

#include "Listener.h"
#include "View.h"
#include "TextStorage.h"

enum Mode { INSERT, COMMAND };

class TextEditor {
public:
    TextEditor() = default;
    void run();
    void update();
    Mode getMode();
    void changeMode(Mode newMode);
private:
    void editText();
    Mode mode;
    Listener listener{};
    View view{};
    TextStorage text;
};


#endif //VIONTEXTEDITOR_TEXTEDITOR_H
