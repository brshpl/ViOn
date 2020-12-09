#ifndef VION_SERVER_INCLUDE_SERVER_H_
#define VION_SERVER_INCLUDE_SERVER_H_

#include <set>
//#include <thread>
#include "../../Socket/Socket.h"


class Server {
public:
    Server() = delete;
    Server(uint32_t port, uint32_t queue_size);
    ~Server() = default;

    void start();
//    void stop();

    void send_changes(const std::string& buf);

    void disconnect_client(std::shared_ptr<Socket> client);

private:
    Socket server_sock;
    std::set<std::shared_ptr<Socket>> clients;

};


#endif  // VION_SERVER_INCLUDE_SERVER_H_
