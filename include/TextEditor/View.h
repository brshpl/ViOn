#ifndef VIONTEXTEDITOR_VIEW_H
#define VIONTEXTEDITOR_VIEW_H

#include "Position.h"
#include "TextStorage.h"

class View {
public:
    Position getCursorPosition();
    void moveCursor(Position newPosition);
    void show(TextStorage text);
private:
    Position cursorPosition;
};


#endif //VIONTEXTEDITOR_VIEW_H
