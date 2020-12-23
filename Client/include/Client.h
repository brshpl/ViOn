#ifndef VION_CLIENT_INCLUDE_CLIENT_H_
#define VION_CLIENT_INCLUDE_CLIENT_H_

#include <string>

//#include "FileController/FileStorage.h"
#include "Parser.h"
#include "Socket.h"


class Client {
public:
    void connectToServer(const std::string& host, int port);

    size_t createNewFile();
    void connectToFile(size_t id);

    void sendChanges(const Change& ch);
    Change recvChanges();
//    void sendChanges(const std::string& buf);
//    std::string recvChanges();

private:
    utils::Socket client_sock_;

};


#endif  // VION_CLIENT_INCLUDE_CLIENT_H_
