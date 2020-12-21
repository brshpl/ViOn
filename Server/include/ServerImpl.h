#ifndef VION_SERVER_INCLUDE_SERVERIMPL_H_
#define VION_SERVER_INCLUDE_SERVERIMPL_H_

#include <set>

#include "EventManager.h"
#include "FileController/FileStorage.h"
#include "Server.h"
#include "Socket.h"


class Server::ServerImpl {
public:
    ServerImpl() = delete;
    ServerImpl(uint32_t port, uint32_t queue_size);
    ~ServerImpl();

    void startImpl();

private:
    utils::Socket server_sock_;
//    std::set<Observer> clients_;
    std::vector<Subject> subject_;
};


#endif  // VION_SERVER_INCLUDE_SERVERIMPL_H_
