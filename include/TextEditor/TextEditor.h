#ifndef VIONTEXTEDITOR_TEXTEDITOR_H
#define VIONTEXTEDITOR_TEXTEDITOR_H

#include "Text.h"
#include "LoginStruct.h"
#include "View.h"

enum Mode { INSERT, COMMAND };

class TextEditor {
public:
    void notify(char symbol, size_t next_symbol_id);
    void update(const Text& text);
//    void set_id_pass(LoginStruct aStruct);

private:
    View view_;
    Mode mode_;
    void changeMode(Mode newMode);
};


#endif //VIONTEXTEDITOR_TEXTEDITOR_H
