#ifndef VION_CLIENT_INCLUDE_CLIENT_H_
#define VION_CLIENT_INCLUDE_CLIENT_H_

#include <string>

#include "Parser.h"
#include "Socket.h"


class Client {
public:
    ~Client();

    void connectToServer(const std::string& host, int port);
    void closeConnect();

    size_t createNewFile();
    ssize_t connectToFile(size_t id);

    void sendChanges(const Change& ch);
    Change recvChanges();

private:
    utils::Socket client_sock_;
};

#endif  // VION_CLIENT_INCLUDE_CLIENT_H_
