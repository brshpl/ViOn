#ifndef VION_CLIENT_INCLUDE_CLIENT_H_
#define VION_CLIENT_INCLUDE_CLIENT_H_

#include <string>

#include "../../change.h"
#include "../../Socket/Socket.h"


class Client {
public:
    Client() = default;
//    Client(const Client& client);
    ~Client() = default;
    void connectToServer(const std::string& host, int port);

    int createNewFile();
    int connectToFile(size_t id, const char* pin);

//    void sendChanges(const change& buf);
//    change* recvChanges();

    void sendChanges(const std::string& buf);
    std::string recvChanges();

private:
    Socket client_sock;

};


#endif  // VION_CLIENT_INCLUDE_CLIENT_H_
