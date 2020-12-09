#include <iostream>

#include <cstdlib>

#include "Client.h"


void Client::connectToServer(const std::string& host, int port) {
    client_sock.connect(host, port);
//    client_sock.setRcvTimeout(3);  // ?
    client_sock.setSndTimeout(3);
}

int Client::create_new_file() { return 0; }
int Client::connect_to_file(size_t id, const char* pin) { return 0; }

//void Client::send_changes(const change* buf) { return 0; }
//change* Client::recv_changes() { return 0; }

void Client::send_changes(const std::string& buf) {
    // buf - структура, превращаем в json
    client_sock.send_size(buf.size());
    client_sock.send(buf);
}
std::string Client::recv_changes() {
    std::string buf;

    buf = client_sock.recv(client_sock.recv_size());

//    buf = client_sock.recv_loop();

    // парсим json, получаем структуру изменений
    return buf;
}