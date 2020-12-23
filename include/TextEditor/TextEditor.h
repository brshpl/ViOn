#ifndef VIONTEXTEDITOR_TEXTEDITOR_H
#define VIONTEXTEDITOR_TEXTEDITOR_H
#include "Message.h"
#include "Client.h"
#include "Mode.h"
#include "Position.h"
#include "Symbol.h"
#include "Text.h"
#include "View.h"

class TextEditor {
public:
    explicit TextEditor(View& view) :
    view_ {view} {}
    void notify(char symbol, Position next_symbol);
    void update(const Text& text);
    void applyChange(const Change& change);
    void sendChange(const Change& change);
    void changeMode(Mode newMode);
    Mode getMode();

private:
    // You must define functions of View, e.g. using ncurses
    View view_;
    Mode mode_ = COMMAND_MODE;
    Client client_;
};


#endif //VIONTEXTEDITOR_TEXTEDITOR_H
