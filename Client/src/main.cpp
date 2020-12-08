#include "Client.h"

#include <iostream>
#include <thread>

using namespace std;


static inline bool is_connect(const string& change) {
    return change == "#";
}


void listen_serv(Client& client) {
    while (true) {
        // Создаем объект change, передаем его слушающей функции
        // пока использую string
        string change_str = client.recv_str();

        cout << change_str << endl;

        if (is_connect(change_str)) {
            break;
        }
    }
}

int main(int argc, char* argv[]) {
    cout << SOURCE_DIR << endl;
    Socket s;
    s.createServerSocket(5000, 3);
    if (argc != 3) {
        // бросить исключение
        std::cout << "no three arguments!" << endl;
        return 1;
    }

    Client client(argv[1], argv[2]);
    if (client.connect_serv() != 0) {
        // что делать есои коннект не случился по разным причинам
        std::cout << "no connect!" << endl;
        return 1;
    }

    thread thread_listen(listen_serv, ref(client)); // пока передаем по ссылке

    while (true) {
        // Вызов функций формирования изменений
        // пока использую string
        string change_str;
        cin >> change_str;

        // client.send_changes(change);
        client.send_str(change_str);

        // Переделать проверку на структуру change
        if (is_connect(change_str)) {
            break;
        }
    }

    thread_listen.join();

    return 0;
}
