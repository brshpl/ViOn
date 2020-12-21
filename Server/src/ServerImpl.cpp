#include <iostream>
#include <thread>

#include "FileController/ChangeApplier.h"
#include "Parser.h"
#include "ServerImpl.h"


size_t linkClientToFile(std::shared_ptr<utils::Socket> client, std::vector<Subject> subject) {
    std::string change;
    change = client->recv();
    std::cout << change << std::endl;
    Change ch = ParserFromJson(change);

    if (ch.cmd == CREATE_FILE) {
        Subject sb;
        sb.Attach(std::make_shared<Observer>(Observer(sb, client)));
        subject.push_back(sb);
        return subject.size() - 1;
    }
    if (ch.cmd == CONNECT_TO_FILE) {
        Subject sb = subject[ch.fileId];
        sb.Attach(std::make_shared<Observer>(Observer(sb, client)));
        return ch.fileId;
    }

    return 0;
}

void handlerClient(std::shared_ptr<utils::Socket> client,
                   std::vector<Subject> &subject) {
    size_t file_id = linkClientToFile(client, subject);

    while (true) {
        std::string change;

        change = client->recv();
        std::cout << change << std::endl;

        Change chstrc = ParserFromJson(change);

        ChangeApplier change_applier(chstrc, std::make_unique<FileStorage>(subject[file_id].getFile()));
        change_applier.applyChange();
        chstrc = change_applier.getChange();

        change = ParserToJson(chstrc);
        //
        std::cout << change << std::endl;

        if (change == "#") {
            client->send(change);
            client->close();

            std::cerr << "Client " << client->getSocket() << " disconnected." << std::endl;
            break;
        }

        subject[file_id].Notify(change);
    }
}

Server::ServerImpl::ServerImpl(uint32_t port, uint32_t queue_size) {
    server_sock_.createServerSocket(port, queue_size);
}

void Server::ServerImpl::startImpl() {
    while (true) {
        std::shared_ptr<utils::Socket> client = server_sock_.accept();

        client->setRcvTimeout(600);

        std::thread th_client(handlerClient,
                              client, std::ref(subject_));
        th_client.detach();

//        clients_.insert(client);

        if (subject_.size() == 100) {
            break;
        }
    }
}

Server::ServerImpl::~ServerImpl() = default;
