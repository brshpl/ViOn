#include <memory>
#include <string>
#include <vector>
#include <iostream>

#include "Direction.h"
#include "Mode.h"
#include "FileController/Message.h"
#include "Symbol.h"
#include "Text.h"
#include "Interpretator.h"
#include "Client.h"

class TextEditor;

class View {
public:
    explicit View(Interpretator& interpretator)
        : interpretator_(interpretator) {}
    virtual void moveCursor(Direction direction);
    void listen(int fd_in, int fd_out);
    virtual void insertChar(char ch);
    virtual void deleteChar(char ch);
    void setText(Text &text);
    std::string_view getStringFromText();
    Mode getMode();
    void changeMode(Mode mode);

    virtual void show(const std::string& text);
protected:
    Mode mode_ = INSERTATION_MODE;
    Text text_;
    Interpretator& interpretator_;

    virtual void notify(int symbol, Position next_symbol);

    virtual void applyChange(const Change& change);
};

class TextEditor {
public:
    explicit TextEditor(View& view) :
            view_ {view} {}
    void update(Text& text) {
        err << text.getTextStr() << std::endl;
        view_.show(text.getTextStr());
        ///
        view_.setText(text);

//        std::string text_show = "Jopa";
//        text_show = text.getTextStr();
    }

private:

    // You must define functions of View, e.g. using ncurses
    View& view_;
};

