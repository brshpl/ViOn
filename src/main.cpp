#include <ChangeCreator.h>
#include "TextEditor.h"
#include "Client.h"
#include <thread>

void run();

int main(int argc, char* argv[]) {
    run();
}

void run() {
//    TextEditor textEditor;
//    Client client = Client();
//    ChangeCreator changeCreator;
//    TextManagerClient textManagerClient;
//    TextStorage textStorage;
//    int connection_ok = client.connect_serv();
//
//    if (connection_ok == 1) {
//        thread Thread(textManagerClient.listen, client, textStorage);
//
//        textEditor.set_id_pass(client.create_new_file());
//        while (true) {
//            char inp = textEditor.listener.listen(1);
//            Change newChange = changeCreator.create_change(inp, textEditor.getContext());
//            client.send_changes(newChange);
//        }
//    }


}