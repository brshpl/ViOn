#ifndef CLIENT_CLIENTEDITOR_H
#define CLIENT_CLIENTEDITOR_H

#include "Client.h"
#include <fstream>


class ClientEditor {
public:
    explicit ClientEditor(const std::string& file_name, int port = 5555, std::string host="localhost");
    void startEdit();

    void save();

private:
    void edit();

    int port_;
    std::string host_;
    Client client_;
    std::shared_ptr<FileStorage> file_storage_;
    std::ofstream file_;
};

#endif //CLIENT_CLIENTEDITOR_H
