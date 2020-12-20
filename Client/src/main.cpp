#include <iostream>
#include <thread>

#include "Client.h"


void listenServ(Client& client) {
    while (true) {
        // Создаем объект change, передаем его слушающей функции
        // пока использую string
        std::string change_str;

        change_str = client.recvChanges();

        std::cout << change_str << std::endl;

        if (change_str == "#") {
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

        while (true) {
            // Вызов функций формирования изменений
            // пока использую string
            std::string change_str;
            std::cin >> change_str;

            // client.sendChanges(Change);
            client.sendChanges(change_str);

            if (change_str == "#") {
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
