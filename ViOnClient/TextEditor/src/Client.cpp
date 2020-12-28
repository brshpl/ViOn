#include <iostream>
#include <cstdlib>

#include "FileController/JsonParser.h"
#include "TextEditor/Client.h"


Client::~Client() = default;

void Client::connectToServer(const std::string& host, int port) {
    client_sock_.connect(host, port);
}

void Client::closeConnect() {
    Position pos;
    Change ch(CLOSE_CONNECT);
    sendChanges(ch);
    ch = recvChanges();
    std::cout << JsonParser::ParseToJson(ch) << std::endl;
}

ssize_t Client::createNewFile() {
    Position pos;
    Change ch(CREATE_FILE);
    sendChanges(ch);

    ch = recvChanges();
    if (ch.cmd != CREATE_FILE) {
        return -1;
    }
    return ch.fileId;
}

ssize_t Client::connectToFile(size_t id) {
    Position pos;
    Change ch(CONNECT_TO_FILE, id, 0, pos, '0');

    sendChanges(ch);
    ch = recvChanges();
    if (ch.cmd == NO_SUCH_FILE_ID) {
        return -1;
    }
    return ch.fileId;
}

void Client::sendChanges(const Change& ch) {
    client_sock_.send(JsonParser::ParseToJson(ch));
}

Change Client::recvChanges() {
    std::string ch;
    ch = client_sock_.recv();

    return JsonParser::ParseFromJson(ch);
}
