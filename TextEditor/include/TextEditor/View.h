#include <memory>
#include <string>
#include <vector>
#include "Direction.h"
#include "Mode.hpp"
#include "Message.hpp"
#include "Position.hpp"
#include "Symbol.h"
#include "Text.h"
#include "Interpretator.hpp"

class TextEditor;

class View {
public:
    explicit View(Interpretator interpretator) : interpretator_{interpretator} {}
    virtual void moveCursor(Direction direction);
    void listen(int fd_in, int fd_out);
    virtual void insertChar(char ch);
    virtual void deleteChar(char ch);
    void setText(Text &text);
    std::string_view getStringFromText();
    Mode getMode();
    void changeMode(Mode mode);
protected:
    Mode mode_ = COMMAND_MODE;
    Text text_;
    void show(const std::string& text);
    Interpretator& interpretator_;
    void notify(int symbol, Position next_symbol);
    void applyChange(const Change& change);
};

class TextEditor {
public:
    explicit TextEditor(View& view) :
            view_ {view} {}
    void update(Text& text);

    void sendChange(const Change& change);

private:

    // You must define functions of View, e.g. using ncurses
    View& view_;

    Client client_; // TODO: add Client.h in CMakeLists.txt
};

