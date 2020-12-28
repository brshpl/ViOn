#ifndef CLIENT_CLIENTEDITOR_H
#define CLIENT_CLIENTEDITOR_H

#include <fstream>
#include "Client.h"
#include "FileController/FileStorage.h"
#include "ChangeCreator.h"


class Client::ClientEditorImpl {
public:
    explicit ClientEditorImpl(const std::string& file_name, int port = 5555, std::string host="localhost");
    void startEdit();

private:
    v
};

#endif //CLIENT_CLIENTEDITOR_H
