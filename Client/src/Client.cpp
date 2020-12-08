#include "Client.h"
#include <thread>
#include <unistd.h>
#include <arpa/inet.h>
#include <stdlib.h>
//#include <netdb.h>

#include <iostream>


Client::Client() {}
Client::Client(const Client& client): sock(client.sock), address(client.address) {}
Client::Client(char* server_ip, char* port) {
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        // бросить исключение
        std::cout << "establishing socket error.\n";
        exit(0);
    }

    address.sin_port = htons(atoi(port));
    address.sin_family = AF_INET;
    inet_pton(AF_INET, server_ip, &address.sin_addr);
}
Client::~Client() {
    close(sock);
}
int Client::connect_serv() {
    return connect(sock, (struct sockaddr*)&address, sizeof(address));
}

int Client::create_new_file() { return 0; }
int Client::connect_to_file(size_t id, const char* pin) { return 0; }

//void Client::send_changes(const change* buf, const size_t size) { return 0; }
//int Client::recv_changes() { return 0; }
void Client::send_str(const std::string& buf) {
    size_t left = buf.size();
    ssize_t sent = 0;
    while (left > 0) {
        sent = send(sock, buf.data() + sent, left, 0);
        if (sent == -1) {
            throw ; // бросить исключение неудачной отправки
        }
        left -= sent;
    }
}
std::string Client::recv_str() {
    char buf[256];
    std::string ret;
    while (true) {
        int n = recv(sock, buf, sizeof(buf), 0);
        if (-1 == n && errno != EAGAIN) {
            throw std::runtime_error("read failed: "/* + std::string(strerror(errno))*/);
        }
        if (0 == n || -1 == n) {  // -1 - timeout
            break;
        }
        ret.append(buf, n);
        // проеверить нужно ли
//        while (ret.back() == '\r' || ret.back() == '\n')
//            ret.pop_back();
    }
    return ret;
}