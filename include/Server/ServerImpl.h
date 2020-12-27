#pragma once

#include <unordered_map>

#include "EventManager.h"
#include "Server.h"


class Server::ServerImpl {
public:
    ServerImpl() = delete;
    ServerImpl(uint32_t port, uint32_t queue_size);
    ~ServerImpl();

    void startImpl();

private:
    utils::Socket server_sock_;
    std::unordered_map<size_t, Subject> subjects_;
};
