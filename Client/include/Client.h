#ifndef VION_CLIENT_INCLUDE_CLIENT_H_
#define VION_CLIENT_INCLUDE_CLIENT_H_

#include <string>

#include "../../Socket/Socket.h"


class Client {
public:
    void connectToServer(const std::string& host, int port);

    void createNewFile();
    void connectToFile(size_t id, const std::string& pin);

//    void sendChanges(const Change& buf);
//    Change recvChanges();
    void sendChanges(const std::string& buf);
    std::string recvChanges();

private:
    Socket client_sock_;

};


#endif  // VION_CLIENT_INCLUDE_CLIENT_H_
