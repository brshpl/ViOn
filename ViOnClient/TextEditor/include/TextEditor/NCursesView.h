#ifndef VION_NCURSES_NCURSESVIEW_H
#define VION_NCURSES_NCURSESVIEW_H

#include "Interpretator.h"
#include "View.h"

#include <utility>
#include "Cursor.h"

class NCursesView : public View {
public:
    explicit NCursesView(Interpretator& interpretator, Client& client)
            : View(interpretator), client_(client) {}
    void listen_test();
    [[noreturn]] void listen();
    void insertChar(const Change& ch);
    void insertString();
    void deleteChar(const Change& ch);


    void moveCursor(Direction direction) override;
private:
    Text text_;
    Cursor cursor;
    Client& client_;

    void show(const std::string& text);

    void notify(int symbol, Position next_symbol);

    void applyChange(const Change &change);
};


#endif //VION_NCURSES_NCURSESVIEW_H
