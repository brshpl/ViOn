#include <iostream>

#include <string>
#include "ClientEditor.h"



int main(int argc, char* argv[]) {
    if (argc != 2) {
        return 1;
    }
    int port = std::stoi(argv[2]);
    std::cout << port;
    ClientEditor editor(port);
    editor.startEdit();

    return 0;
}
