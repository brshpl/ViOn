#include "Server.h"
#include "handler.h"

Server::Server(int _socket, struct sockaddr_in _address) {}
Server::~Server() {}

void Server::start() {}
void Server::stop() {}

int Server::accept_connections() { return 0; }
