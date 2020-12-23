#include <iostream>

#include <cstdlib>

#include "Client.h"


void Client::connectToServer(const std::string& host, int port) {
    client_sock_.connect(host, port);

    client_sock_.setSndTimeout(3);
}

size_t Client::createNewFile() {
    Position pos = {0};
    Change ch = Change(CREATE_FILE, 0, pos, 0, '0');
    sendChanges(ch);

    ch = recvChanges();
    return ch.fileId;
}

void Client::connectToFile(size_t id) {
    Position pos = {0};
    Change ch = Change(CONNECT_TO_FILE, id, pos, 0, '0');
    sendChanges(ch);
}

void Client::sendChanges(const Change& ch) {
    client_sock_.send(ParserToJson(ch));
}

Change Client::recvChanges() {
    std::string ch;
    ch = client_sock_.recv();

    return ParserFromJson(ch);
}

//void Client::sendChanges(const std::string& buf) {
//    // buf - структура, превращаем в json, отправляем на сервер
//    client_sock_.send(buf);
//}
//
//std::string Client::recvChanges() {
//    std::string buf;
//
//    buf = client_sock_.recv();
//
//    // парсим json, получаем структуру изменений, возвращаем ее
//    return buf;
//}
