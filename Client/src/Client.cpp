#include <iostream>
#include <cstdlib>

#include "Client.h"


Client::~Client() {
    closeConnect();
}

void Client::connectToServer(const std::string& host, int port) {
    client_sock_.connect(host, port);
}

void Client::closeConnect() {
    Position pos = {0};
    Change ch = Change(CLOSE_CONNECT, 0, pos, 0, '0');
    sendChanges(ch);
}

size_t Client::createNewFile() {
    Position pos = {0};
    Change ch = Change(CREATE_FILE, 0, pos, 0, '0');
    sendChanges(ch);

    ch = recvChanges();
    return ch.fileId;
}

size_t Client::connectToFile(size_t id) {
    Position pos = {0};
    Change ch = Change(CONNECT_TO_FILE, id, pos, 0, '0');
    sendChanges(ch);

    ch = recvChanges();
    return ch.fileId;
}

void Client::sendChanges(const Change& ch) {
    client_sock_.send(ParserToJson(ch));
}

Change Client::recvChanges() {
    std::string ch;
    ch = client_sock_.recv();

    return ParserFromJson(ch);
}
