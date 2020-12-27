#ifndef VION_SERVER_INCLUDE_SERVER_H_
#define VION_SERVER_INCLUDE_SERVER_H_

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

#endif  // VION_SERVER_INCLUDE_SERVER_H_
