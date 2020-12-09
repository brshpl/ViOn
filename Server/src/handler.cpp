#include <iostream>
#include <thread>

#include "handler.h"

static inline bool is_connect(const std::string& change) {
    return change == "#";
}


void listen_client(std::shared_ptr<Socket> client) {
    while (true) {
        // Создаем объект change, передаем его слушающей функции
        // пока использую string

        std::string change_str = client->recv(client->recv_size());

        std::cout << change_str << std::endl;

        if (is_connect(change_str)) {
            break;
        }
    }
}

void handler_client(std::shared_ptr<Socket> client) {
    std::thread thread_listen(listen_client, client);

    while (true) {
        // Вызов функций формирования изменений
        // пока использую string
        std::string change_str;
        std::cin >> change_str;

        // client.send_changes(change);
        client->send_size(change_str.size());
        client->send(change_str);

        // Переделать проверку на структуру change
        if (is_connect(change_str)) {
            break;
        }
    }

    thread_listen.join();
}

//int send_changes(const change* buf, const size_t size) {}
//change* recv_changes() {}
