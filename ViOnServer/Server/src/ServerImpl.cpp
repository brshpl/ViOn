#include <atomic>
#include <shared_mutex>
#include <thread>

#include "FileController/JsonParser.h"
#include "ServerImpl.h"
#include "FileIds.h"


static std::shared_mutex mtx;
static std::mutex mtx_file_id;
static FileIds file_ids;

void handlerClient(std::shared_ptr<utils::Socket> client, std::unordered_map<size_t, Subject>& subjects) {
    std::string request_str;
    Change request;
    Observer* observer;
    size_t file_id;

    try {
        request_str = client->recv();
        request = JsonParser::ParseFromJson(request_str);

        std::shared_lock<std::shared_mutex> s_lock(mtx, std::defer_lock);
        switch (request.cmd) {
            case CREATE_FILE: {
                std::unique_lock<std::mutex> lock(mtx_file_id);
                file_id = file_ids.getFileId();
                lock.unlock();

                std::unique_lock<std::shared_mutex> u_lock(mtx);
                subjects.insert(std::pair<size_t, Subject>(file_id, Subject(file_id)));
                std::clog << "CREATE_FILE" << std::endl;
                break;
            }
            case CONNECT_TO_FILE: {
                s_lock.lock();
                while (subjects.count(request.fileId) == 0 && request.cmd == CONNECT_TO_FILE) {
                    std::clog << " CONNECT_TO_FILE: no such file" << std::endl;
                    request.cmd = NO_SUCH_FILE_ID;
                    client->send(JsonParser::ParseToJson(request));
                    request_str = client->recv();
                    request = JsonParser::ParseFromJson(request_str);
                }
                file_id = request.fileId;
                break;
            }
            default: {
                //
                return;
            }
        }
        request.fileId = file_id;

        client->send(JsonParser::ParseToJson(request));

        observer = new Observer(subjects[file_id], client);
        if (s_lock) s_lock.unlock();

        observer->updateFile();
        observer->editFile();

    } catch (...) {
        std::cerr << "Client dead" << std::endl;
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
