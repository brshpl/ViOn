#include <string>
#include "ClientEditor.h"


int main(int argc, char* argv[]) {
    if (argc != 3) {
        return 1;
    }
    int port = std::stoi(argv[2]);

    ClientEditor editor(argv[1], port);
    editor.startEdit();

    return 0;
}
