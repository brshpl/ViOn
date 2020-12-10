#include <iostream>

#include <cstdlib>

#include "Client.h"


void Client::connectToServer(const std::string& host, int port) {
    client_sock_.connect(host, port);

    client_sock_.setSndTimeout(3);
}

void Client::createNewFile() {}

void Client::connectToFile(size_t id, const std::string& pin) {}

void Client::sendChanges(const std::string& buf) {
    // buf - структура, превращаем в json, отправляем на сервер
    client_sock_.send(buf);
}

std::string Client::recvChanges() {
    std::string buf;

    buf = client_sock_.recv();

    // парсим json, получаем структуру изменений, возвращаем ее
    return buf;
}
