#include <ncurses.h>
#include <cstring>
#include <string_view>
#include <vector>
#include <NCursesView.h>

#define CREATE_FILE 1
#define CONNECT_TO_FILE 2
#define EXIT 'q'

int mainMenu();
void createFileView();
void connectToFileView();
int connectToFile();
int createFile();
void runTextEditor(int file_id);
void show(std::string_view text);
void moveCursor(char direction);

int main()
{
    initscr();
    while (true) {
        int cmd = mainMenu();
        switch (cmd) {
            case CREATE_FILE:
                createFileView();
                break;
            case CONNECT_TO_FILE:
                connectToFileView();
                break;
            case EXIT:
                endwin();
                return 0;
            default:
                break;
        }
    }
}

int mainMenu() {
    std::vector<std::string_view> menu {
            "Menu",
            "F1 - Create file",
            "F2 - Connect to file",
            "Q  - Exit"
    };

    int row, col;
    getmaxyx(stdscr, row, col);

    clear();
    for (size_t i = 0; i < menu.size(); ++i) {
        mvwaddstr(stdscr, row / 2 - menu.size() / 2 + i, (col - menu.at(i).length()) / 2, menu.at(i).data());
    }
    curs_set(0);
    keypad(stdscr, true);
    noecho();
    while (true) {
        switch (getch()) {
            case KEY_F(1):
                clear();
                return CREATE_FILE;
            case KEY_F(2):
                clear();
                return CONNECT_TO_FILE;
            case EXIT:
                clear();
                return EXIT;
            default:
                mvwaddstr(stdscr, row - 1, 0, "Print F1 or F2");
                break;
        };
    }
}

void createFileView() {
    int row = getmaxy(stdscr);
    int file_id = createFile();
    if (file_id != -1) {
        runTextEditor(file_id);
    } else {
        clear();
        mvprintw(row - 1, 0, "File creating failed. Press any key to get back to main menu...", file_id);
        getch();
    }
}

void connectToFileView() {
    int row = getmaxy(stdscr);
    mvwaddstr(stdscr, row - 1, 0, "Input file id: ");
    curs_set(1);
    echo();
    int file_id = 0;
    scanw("%d", &file_id);
    clear();
    mvprintw(row - 1, 0, "Connecting to file with id=%d. Please wait...", file_id);
    if (connectToFile() == 1) {
        runTextEditor(file_id);
    } else {
        clear();
        mvprintw(row - 1, 0, "Connection failed. Press any key to get back to main menu...", file_id);
        getch();
    }
}

int connectToFile() {
//    return client_.;
    return 0;
}

int createFile() {
    return 0;
}

void runTextEditor(int file_id) {
    Interpretator interpretator;
    NCursesView view(interpretator);
    TextEditor textEditor(view);
//    view.listen_test();

}

void show(std::string_view text) {
    clear();
    mvprintw(0, 0, "%s", text.data());
}
