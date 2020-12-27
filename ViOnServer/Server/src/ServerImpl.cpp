#include <atomic>
#include <shared_mutex>
#include <thread>

#include "FileController/JsonParser.h"
#include "ServerImpl.h"

static std::shared_mutex mtx;
static std::atomic<size_t> numberOfFilesCreated;

void handlerClient(std::shared_ptr<utils::Socket> client, std::unordered_map<size_t, Subject>& subjects) {
    std::string request_str;
    request_str = client->recv();
    Change request = JsonParser::ParseFromJson(request_str);

    size_t file_id;

    std::shared_lock<std::shared_mutex> s_lock(mtx, std::defer_lock);
    switch (request.cmd) {
        case CREATE_FILE: {
            file_id = ++numberOfFilesCreated;
            std::unique_lock<std::shared_mutex> u_lock(mtx);
            subjects.insert(std::pair<size_t, Subject>(file_id, Subject(file_id)));
            std::cout << "CREATE_FILE" << std::endl;
            break;
        }
        case CONNECT_TO_FILE: {
            s_lock.lock();
            while (subjects.count(request.fileId) == 0 && request.cmd == CONNECT_TO_FILE) {
                std::cout << " CONNECT_TO_FILE: такого файла нет" << std::endl;
                request.cmd = NO_SUCH_FILE_ID;
                client->send(JsonParser::ParseToJson(request));
                request_str = client->recv();
                request = JsonParser::ParseFromJson(request_str);
            }
            file_id = request.fileId;   // logic fileId
            break;
        }
        default: {
            //
            return;
        }
    }
    request.fileId = file_id;
    try {
        client->send(JsonParser::ParseToJson(request));
    } catch (...) {
        std::cerr << "ParseToJson" << std::endl;
    }

    auto* observer = new Observer(subjects[file_id], client);
    if (s_lock) s_lock.unlock();

    try {
        observer->updateFile();
        observer->editFile();
    } catch (...) {
        std::cerr << "editFile" << std::endl;
    }

    observer->removeMeFromTheList();
    delete observer;

    if (subjects[file_id].amountOfObservers() == 0) {
        std::unique_lock<std::shared_mutex> u_lock(mtx);
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
