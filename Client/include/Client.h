#ifndef VION_CLIENT_INCLUDE_CLIENT_H_
#define VION_CLIENT_INCLUDE_CLIENT_H_

//#include "change.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <string>
#include "../../Socket/Socket.h"


class Client {
public:
    Client();
    Client(const Client& client);
    Client(char* server_ip, char* port);
    ~Client();
    int connect_serv();

    int create_new_file();
    int connect_to_file(size_t id, const char* pin);

//    void send_changes(const change* buf, const size_t size);
//    int recv_changes();
    void send_str(const std::string& buf);
    std::string recv_str();

private:
    int sock;
    struct sockaddr_in address;

};


#endif  // VION_CLIENT_INCLUDE_CLIENT_H_
