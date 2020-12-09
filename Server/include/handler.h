#ifndef VION_SERVER_INCLUDE_HANDLER_H_
#define VION_SERVER_INCLUDE_HANDLER_H_

//#include "change.h"
#include "../../Socket/Socket.h"


void handler_client(std::shared_ptr<Socket> client);

//int send_changes(const change* buf, const size_t size);
//change* recv_changes();

#endif  // VION_SERVER_INCLUDE_HANDLER_H_
