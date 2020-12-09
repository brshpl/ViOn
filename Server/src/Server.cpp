#include <iostream>
#include <thread>

#include "Server.h"


void handler_client(Server& server, std::shared_ptr<Socket> client) {
    while (true) {
        std::string change_str;

        try {
            change_str = client->recv();
        }
        catch (const std::exception& e) {
            server.disconnect_client(client);

            std::cerr << e.what() << std::endl;
            break;
        }
        std::cout << change_str << std::endl;

        // Применение изменений к файлу на сервере

        if (change_str == "#") {
            client->send(change_str);
            server.disconnect_client(client);
            std::cerr << "Client " << client->get_socket() << " disconnected." << std::endl;
            break;
        }

        server.send_changes(change_str);
    }
}

Server::Server(uint32_t port, uint32_t queue_size) {
    server_sock.createServerSocket(port, queue_size);
}

void Server::start() {
    while (true) {
        std::shared_ptr<Socket> client = server_sock.accept();

        client->setRcvTimeout(600);

        std::thread th_client(handler_client, std::ref(*this), client);
        th_client.detach();

        clients.insert(client);

        if (clients.size() == 100) {
            break;
        }
    }
}

void Server::send_changes(const std::string &buf) {
    // buf - структура, превращаем в json

    for (const auto& client : clients) {
        client->send(buf);
    }
}

void Server::disconnect_client(std::shared_ptr<Socket> client) {
    clients.erase(client);
    client->close();    // Нужно ли???

}
