#include "Client.h"
#include <thread>


Client(int _socket, struct sockaddr_in _address) {}
~Client() {}
int connect_serv() { return 0; }

int create_new_file() { return 0; }
int connect_to_file(size_t id, const char* pin) { return 0; }

int send_changes(const change* buf, const size_t size) { return 0; }
int recv_changes() { return 0; }

change* get_change() {}
