#include "ClientEditor.h"
#include "TextEditor/ClientEditorImpl.h"


ClientEditor::ClientEditor(const std::string &file_name, int port, std::string host)
        : p_impl_(std::make_unique<ClientEditorImpl>(file_name, port, host)) {}

void ClientEditor::startEdit() {
    p_impl_->startEdit();
}

ClientEditor::~ClientEditor() = default;



