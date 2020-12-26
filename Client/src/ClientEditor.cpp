#include <thread>
#include <utility>

#include "ClientEditor.h"
#include "FileController/ChangeApplier.h"



void listenServ(Client& client, std::shared_ptr<FileStorage> file) {
    Change change;
    do {
        change = client.recvChanges();

        ChangeApplier change_applier(change, file);
        change_applier.applyChange();

        std::cout << "File №" << file->file_id << " : <";
        for (SymbolState s : file->symbols) {
            if (s.is_visible) {
                std::cout << s.symbol;
            }
        }
        std::cout << ">" << std::endl;
    } while (change.cmd != CLOSE_CONNECT);
}

ClientEditor::ClientEditor(int port, std::string host): port_(port), host_(std::move(host)) {
    try {
        client_.connectToServer(host_, port_);
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }

    file_ = std::make_shared<FileStorage>();
}

void ClientEditor::startEdit() {
    ssize_t file_id;

    std::cout << "1. create\n"
              << "2. connect" << std::endl;
    switch (std::cin.get()) {
        case '1': {
            file_id = client_.createNewFile();
            break;
        }
        case '2': {
            do {
                std::cin >> file_id;
                file_id = client_.connectToFile(file_id);
            } while (file_id == -1);
            break;
        }
    }
    file_->file_id = file_id;
    std::cout << "File id: " << file_id << std::endl;

    std::thread thread_listen(listenServ, std::ref(client_), file_);
    edit();
    thread_listen.join();
}

void ClientEditor::edit() {
    Change change;
//    Position pos = {0};

    while (change.cmd != CLOSE_CONNECT) {
        char change_c;
        std::cin >> change_c;

        change.cmd = (change_c == '#') ? CLOSE_CONNECT : INSERT_SYMBOL;
        change.symbol = change_c;

        client_.sendChanges(change);
    } // while (change.cmd != CLOSE_CONNECT);
}

