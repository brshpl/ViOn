#include <iostream>
#include <thread>

#include "handler.h"
#include "Server.h"

#include <list>


int main(int argc, char* argv[]) {
//    std::list<int> l;
//    l.;

    if (argc != 2) {
        std::cout << "no arguments!" << std::endl;
        return 1;
    }
    int port = std::stoi(argv[1]);

    try {
        Server server(handler_client);
        server.start(port, 5);
    }
    catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
