#ifndef CLIENT_CLIENTEDITOR_H
#define CLIENT_CLIENTEDITOR_H

#include "Client.h"


class ClientEditor {
public:
    explicit ClientEditor(int port = 5555, std::string  host="localhost");
    void startEdit();

private:
    void edit();

    int port_;
    std::string host_;
    Client client_;
    std::shared_ptr<FileStorage> file_;
};

#endif //CLIENT_CLIENTEDITOR_H
