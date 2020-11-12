#ifndef VION_SERVER_INCLUDE_HANDLER_H_
#define VION_SERVER_INCLUDE_HANDLER_H_

#include "change.h"


void handler_client(int socket_connect);

int send_changes(const change* buf, const size_t size);
change* recv_changes();

#endif  // VION_SERVER_INCLUDE_HANDLER_H_
