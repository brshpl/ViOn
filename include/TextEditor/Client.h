#ifndef VION_CLIENT_INCLUDE_CLIENT_H_
#define VION_CLIENT_INCLUDE_CLIENT_H_

#include <string>
#include "Message.h"

class Client {
public:
    void connectToServer(const std::string& host, int port);

    void createNewFile();
    void connectToFile(std::string file_id);


    void sendChanges(const Change& buf);
    Change recvChanges();
};


#endif  // VION_CLIENT_INCLUDE_CLIENT_H_