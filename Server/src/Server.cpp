#include <iostream>
#include <thread>

#include "Server.h"


void handlerClient(Server& server, std::shared_ptr<Socket> client) {
    while (true) {
        std::string change_str;

        try {
            change_str = client->recv();
        }
        catch (const std::exception& e) {
            server.disconnectClient(client);

            std::cerr << e.what() << std::endl;
            break;
        }
        std::cout << change_str << std::endl;

        // Применение изменений к файлу на сервере

        if (change_str == "#") {
            client->send(change_str);
            server.disconnectClient(client);
            std::cerr << "Client " << client->getSocket() << " disconnected." << std::endl;
            break;
        }

        server.sendChanges(change_str);
    }
}

Server::Server(uint32_t port, uint32_t queue_size) {
    server_sock_.createServerSocket(port, queue_size);
}

void Server::start() {
    while (true) {
        std::shared_ptr<Socket> client = server_sock_.accept();

        client->setRcvTimeout(600);

        std::thread th_client(handlerClient, std::ref(*this), client);
        th_client.detach();

        clients_.insert(client);

        if (clients_.size() == 100) {
            break;
        }
    }
}

void Server::sendChanges(const std::string &buf) {
    // buf - структура, превращаем в json

    for (const auto& client : clients_) {
        client->send(buf);
    }
}

void Server::disconnectClient(std::shared_ptr<Socket> client) {
    clients_.erase(client);
    client->close();

}
