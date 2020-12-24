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

        for (SymbolState s : file->symbols)
            if (s.is_visible)
                std::cout << s.symbol << std::endl;


//        std::cout << ParserToJson(change) << std::endl;
//        std::cout << change.symbol << std::endl;
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
    size_t file_id;

    std::cout << "1. create\n"
              << "2. connect" << std::endl;
    switch (std::cin.get()) {
        case '1': {
            file_id = client_.createNewFile();
            break;
        }
        case '2': {
            std::cin >> file_id;
            file_id = client_.connectToFile(file_id);
            break;
        }
    }
    std::cout << "File id: " << file_id << std::endl;

    std::thread thread_listen(listenServ, std::ref(client_), file_);
    edit();
    thread_listen.join();
}

void ClientEditor::edit() {
    Change change;
    Position pos = {0};
    do {
        char change_c;

//        change_c = getch();
        std::cin >> change_c;

        Command cmd = (change_c == '#') ? CLOSE_CONNECT : INSERT_SYMBOL;


        change = Change(cmd, 0, pos, 0, change_c);

        if (change_c == '1') {
            change = Change(DELETE_SYMBOL, 0, pos, 1, 's');
        }

        client_.sendChanges(change);

//        pos.symbolId++;
    } while (change.cmd != CLOSE_CONNECT);
}

