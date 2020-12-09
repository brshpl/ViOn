#ifndef VION_SERVER_INCLUDE_SERVER_H_
#define VION_SERVER_INCLUDE_SERVER_H_

#include <functional>
//#include <thread>
#include "../../Socket/Socket.h"


class Server {
public:
    Server() = delete;
    explicit Server(void (*_handler_client)(std::shared_ptr<Socket>)) : handler_client(_handler_client) {}
    ~Server() = default;

    void start(uint32_t port, uint32_t queue_size);
    void stop();

private:
    Socket server_sock;
    std::vector<std::shared_ptr<Socket>> clients;

    void (*handler_client)(std::shared_ptr<Socket>);
//    typedef std::function<void(Socket)> handler_function_t;

};


#endif  // VION_SERVER_INCLUDE_SERVER_H_
