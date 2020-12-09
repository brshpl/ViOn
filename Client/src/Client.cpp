#include <iostream>

#include <cstdlib>
//#include <nlohmann/json.hpp>

#include "Client.h"


void Client::connectToServer(const std::string& host, int port) {
    client_sock.connect(host, port);

    client_sock.setSndTimeout(3); // нужно?
}

int Client::createNewFile() { return 0; }
int Client::connectToFile(size_t id, const char* pin) { return 0; }

/*void Client::sendChanges(const change& buf) {
    // buf - структура, превращаем в json
    client_sock.send(buf);
}
std::string Client::recvChanges() {
    std::string buf;

    buf = client_sock.recv();

    // парсим json, получаем структуру изменений
    return buf;
}*/


void Client::sendChanges(const std::string& buf) {
    // buf - структура, превращаем в json
    client_sock.send(buf);
}
std::string Client::recvChanges() {
    std::string buf;

    buf = client_sock.recv();

    // парсим json, получаем структуру изменений
    return buf;
}
