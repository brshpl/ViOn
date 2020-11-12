#ifndef VION_SERVER_INCLUDE_SERVER_H_
#define VION_SERVER_INCLUDE_SERVER_H_

#include <sys/socket.h>
#include <thread>


class Server {
public:
    Server(int _socket, struct sockaddr_int _address);
    ~Server();

    void start();
    void stop();

private:
    int accept_connections();

private:
    int socket;
    struct sockaddr_in address;

};


#endif  // VION_SERVER_INCLUDE_SERVER_H_
