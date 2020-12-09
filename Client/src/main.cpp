#include <iostream>
#include <thread>

#include "Client.h"


static inline bool is_connect(const std::string& change) {
    return change == "#";
}


void listen_serv(Client& client) {
    while (true) {
        // Создаем объект change, передаем его слушающей функции
        // пока использую string
        std::string change_str = client.recv_changes();

        std::cout << change_str << std::endl;

        if (is_connect(change_str)) {
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

        std::thread thread_listen(listen_serv, std::ref(client));

        while (true) {
            // Вызов функций формирования изменений
            // пока использую string
            std::string change_str;
            std::cin >> change_str;

            // client.send_changes(change);
            client.send_changes(change_str);

            // Переделать проверку на структуру change
            if (is_connect(change_str)) {
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
