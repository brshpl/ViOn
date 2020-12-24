#include <iostream>
#include <thread>
#include <mutex>

#include "Parser.h"
#include "ServerImpl.h"


static size_t numberOfFilesCreated = 0;
std::mutex mtx;

void handlerClient(std::shared_ptr<utils::Socket> client, std::map<size_t, Subject>& subjects) {
    std::string request_str;
    request_str = client->recv();
    Change request = ParserFromJson(request_str);

    mtx.lock();
    size_t file_id = numberOfFilesCreated;

    switch (request.cmd) {
        case CREATE_FILE: {
            Subject subject;
            subjects.insert(std::pair<size_t, Subject>(numberOfFilesCreated++, subject));
            break;
        }
        case CONNECT_TO_FILE: {
            file_id = request.fileId;   // logic fileId
            break;
        }
        case CLOSE_CONNECT: {
            //
            return;
            break;
        }
        default: {
            //
            return;
        }
    }
    mtx.unlock();

    std::shared_ptr<Observer> observer = std::make_shared<Observer>(subjects[file_id], client);

    request.fileId = file_id;
    client->send(ParserToJson(request));

    observer->editFile();

    if (subjects[file_id].amountOfObservers() == 0) {
        subjects.erase(file_id);
    }
}

Server::ServerImpl::ServerImpl(uint32_t port, uint32_t queue_size) {
    server_sock_.createServerSocket(port, queue_size);
}

void Server::ServerImpl::startImpl() {
    while (true) {
        std::shared_ptr<utils::Socket> client = server_sock_.accept();
        client->setRcvTimeout(600);

        std::thread th_client(handlerClient, client, std::ref(subjects_));
        th_client.detach();

        if (subjects_.size() == 100) {
            break;
        }
    }
}

Server::ServerImpl::~ServerImpl() = default;
