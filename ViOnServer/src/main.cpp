#include <iostream>

#include "Server.h"
#include "FileIds.h"


int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cout << "no arguments!" << std::endl;
        return 1;
    }
    uint32_t port = std::stoi(argv[1]);

    try {
        Server server(port, 5);
        server.start();
    }
    catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
