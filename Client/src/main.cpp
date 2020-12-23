#include <iostream>
#include <thread>

#include "Client.h"


void listenServ(Client& client) {
    while (true) {
        Change ch;

        ch = client.recvChanges();

        std::cout << ParserToJson(ch) << std::endl;

        if (ch.symbol == '#') {
            break;
        }
    }
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cout << "no three arguments!" << std::endl;
        return 1;
    }
    std::string host(argv[1]);
    int port = std::stoi(argv[2]);

    Client client;

    try {
        client.connectToServer(host, port);

        std::thread thread_listen(listenServ, std::ref(client));
        size_t file_id;

        std::string command;
        std::cin >> command;
        if (command == "create") {
            file_id = client.createNewFile();
        }
        if (command == "connect") {
            std::cin >> file_id;
            client.connectToFile(file_id);
        }

        Position pos = {0};
        while (true) {
            char change;
            std::cin >> change;

            Change ch = Change(INSERT_SYMBOL, file_id, pos, 0, change);

            // client.send_changes(change);
            client.sendChanges(ch);

            pos.symbolId++;

            if (change == '#') {
                break;
            }
        }

        thread_listen.join();
    }
    catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
