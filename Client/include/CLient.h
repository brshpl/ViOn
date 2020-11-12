#ifndef VION_CLIENT_INCLUDE_CLIENT_H_
#define VION_CLIENT_INCLUDE_CLIENT_H_

#include "change.h"
#include <sys/socket.h>
#include <thread>


class CLient {
public:
    Client(int _socket, struct sockaddr_in _address);
    ~Client();
    int connect_serv();

    int create_new_file();
    int connect_to_file(size_t id, const char* pin);

    int send_changes(const change* buf, const size_t size);
    int recv_changes();

    change* get_change();

private:
    int socket;
    struct sockaddr_in address;
    change buffer;

};


#endif  // VION_CLIENT_INCLUDE_CLIENT_H_
