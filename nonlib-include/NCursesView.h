//
// Created by brshpl on 24.12.2020.
//

#ifndef VION_NCURSES_NCURSESVIEW_H
#define VION_NCURSES_NCURSESVIEW_H

#include "Interpretator.h"
#include "View.h"

#include <utility>
#include "Cursor.h"

class NCursesView : public View {
public:
    explicit NCursesView(Interpretator interpretator)
    : View(std::move(interpretator)) {}

    void listen_test();
    [[noreturn]] void listen();
    void insertChar(char ch) override;
    void insertString();
    void deleteChar(char ch) override;


    void moveCursor(Direction direction) override;
private:
    Text text_;
    Cursor cursor;

    void show(const std::string& text);

    void notify(int symbol, Position next_symbol);

    void applyChange(const Change &change);
};


#endif //VION_NCURSES_NCURSESVIEW_H
