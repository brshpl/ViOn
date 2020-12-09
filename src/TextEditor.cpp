#include "TextEditor.h"
#include "Interpretator.h"

void TextEditor::changeMode(Mode newMode) {

}

void TextEditor::update(const Text &text) {

}

void TextEditor::notify(char symbol, size_t next_symbol_id) {
    Interpretator interpretator;
    interpretator.interpret(symbol, next_symbol_id, mode_);
}
