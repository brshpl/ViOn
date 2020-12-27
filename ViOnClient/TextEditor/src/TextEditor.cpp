#include "Direction.h"
#include "Interpretator.h"
#include "View.h"



void TextEditor::sendChange(const Change &change) {
//    client_.sendChanges(change);
}

void TextEditor::update(Text& text) {
    view_.setText(text);
}
