#ifndef VION_CLIENT_INCLUDE_CLIENT_H_
#define VION_CLIENT_INCLUDE_CLIENT_H_

#include <string>

//#include "change.h"
#include "../../Socket/Socket.h"


class Client {
public:
    Client() = default;
//    Client(const Client& client);
    ~Client() = default;
    void connectToServer(const std::string& host, int port);

    int create_new_file();
    int connect_to_file(size_t id, const char* pin);

//    void send_changes(const change* buf);
//    change* recv_changes();

    void send_changes(const std::string& buf);
    std::string recv_changes();

private:
    Socket client_sock;

};


#endif  // VION_CLIENT_INCLUDE_CLIENT_H_
