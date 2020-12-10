#ifndef VION_SERVER_INCLUDE_SERVER_H_
#define VION_SERVER_INCLUDE_SERVER_H_

#include <set>

#include "../../Socket/Socket.h"


class Server {
public:
    Server() = delete;
    Server(uint32_t port, uint32_t queue_size);
    ~Server() = default;

    void start();

    void sendChanges(const std::string& buf);

    void disconnectClient(std::shared_ptr<Socket> client);

private:
    Socket server_sock_;
    std::set<std::shared_ptr<Socket>> clients_;

};


#endif  // VION_SERVER_INCLUDE_SERVER_H_
