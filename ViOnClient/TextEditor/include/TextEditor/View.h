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
    explicit View(Interpretator interpretator, int port = 5555, std::string host="localhost")
        : interpretator_{interpretator} {
        try {
            client_.connectToServer(host, port);
        } catch (const std::exception& e) {
            std::cerr << e.what() << std::endl;
        }
    }
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

    Client client_;
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
};

