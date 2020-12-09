#include <thread>

#include "Server.h"


void Server::start(uint32_t port, uint32_t queue_size) {
    server_sock.createServerSocket(port, queue_size);

    while (true) {
        std::shared_ptr<Socket> client = server_sock.accept();

//        client->setRcvTimeout(3);

        std::thread th_client(handler_client, client);  // Переделать: handler_client -  функция член класса
        th_client.detach();

        clients.push_back(client);

        if (clients.size() == 2) {
            stop();
            break;
        }
    }
}
void Server::stop() {}
