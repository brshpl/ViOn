#pragma once

#include <memory>


class Server {
public:
    Server() = delete;
    Server(uint32_t port, uint32_t queue_size);
    ~Server();

    void start();

private:
    class ServerImpl;
    std::unique_ptr<ServerImpl> p_impl_;
};
