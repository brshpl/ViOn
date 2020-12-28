#ifndef CLIENT_CLIENTEDITOR_H
#define CLIENT_CLIENTEDITOR_H

#include <memory>
#include <string>


class ClientEditor {
public:
    ClientEditor() = delete;
    explicit ClientEditor(const std::string& file_name, int port = 5555, std::string host="localhost");
    void startEdit();
    ~ClientEditor();

private:
    class ClientEditorImpl;
    std::unique_ptr<ClientEditorImpl> p_impl_;
};

#endif //CLIENT_CLIENTEDITOR_H
