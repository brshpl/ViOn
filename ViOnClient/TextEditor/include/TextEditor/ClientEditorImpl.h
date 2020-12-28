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
    void save();
    void createFileView();
    void connectToFileView();

    void runTextEditor();
    void edit();

private:
    int port_;
    std::string host_;
    Client client_;
    std::shared_ptr<FileStorage> file_storage_;
    std::ofstream file_;
    ChangeCreator changeCreator_;
};

#endif //CLIENT_CLIENTEDITOR_H
