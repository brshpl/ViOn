#include <iostream>
#include <thread>

#include "ServerImpl.h"


void sendChanges(const std::string &buf, std::set<std::shared_ptr<Socket>> &clients) {
    for (const auto& client : clients) {
        client->send(buf);
    }
}

void handlerClient(std::shared_ptr<Socket> client,
                   std::set<std::shared_ptr<Socket>> &clients) {
    while (true) {
        std::string change_str;

        change_str = client->recv();

        //
        std::cout << change_str << std::endl;

        // Применение изменений к файлу на сервере

        if (change_str == "#") {
            client->send(change_str);
            clients.erase(client);
            client->close();

            std::cerr << "Client " << client->getSocket() << " disconnected." << std::endl;
            break;
        }

        sendChanges(change_str, clients);
    }
}

Server::ServerImpl::ServerImpl(uint32_t port, uint32_t queue_size) {
    server_sock_.createServerSocket(port, queue_size);
}

void Server::ServerImpl::startImpl() {
    while (true) {
        std::shared_ptr<Socket> client = server_sock_.accept();

        client->setRcvTimeout(600);

        std::thread th_client(handlerClient,
                              client, std::ref(clients_));
        th_client.detach();

        clients_.insert(client);

        if (clients_.size() == 100) {
            break;
        }
    }
}

Server::ServerImpl::~ServerImpl() = default;
