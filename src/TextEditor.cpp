#include "Direction.h"
#include "Interpretator.h"
#include "TextEditor.h"

void TextEditor::notify(char symbol, Position next_symbol) {
    Change cur_change = Interpretator().Interpret(symbol, mode_, next_symbol);
    applyChange(cur_change);
}

void TextEditor::changeMode(Mode newMode) {
    mode_ = newMode;
}

void TextEditor::sendChange(const Change &change) {
    client_.sendChanges(change);
}

void TextEditor::applyChange(const Change &change) {
    switch (change.cmd) {
        case NOTHING:
            break;
        case MOVE_UP:
            view_.moveCursor(UP);
            break;
        case MOVE_DOWN:
            view_.moveCursor(DOWN);
            break;
        case MOVE_RIGHT:
            view_.moveCursor(RIGHT);
            break;
        case MOVE_LEFT:
            view_.moveCursor(LEFT);
            break;
        case CHANGE_MODE: {
            Mode newMode = (mode_ == COMMAND_MODE) ? INSERTATION_MODE : COMMAND_MODE;
            changeMode(newMode);
            break;
        }
        case CREATE_FILE:
            client_.createNewFile();
            break;
        case INSERT_SYMBOL:
            view_.insertChar(change.symbol);
            sendChange(change);
            break;
        case DELETE_SYMBOL:
            view_.deleteChar(change.symbol);
            sendChange(change);
            break;
        default:
            break;
    }
}

Mode TextEditor::getMode() {
    return mode_;
}

void TextEditor::update(const Text& text) {
    view_.setText(text);
}
