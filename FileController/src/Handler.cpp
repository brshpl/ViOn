#include "FileController/Handler.h"

std::shared_ptr<Handler> AbstractHandler::SetNext(std::shared_ptr<Handler> handler) {
    this->next_handler_ = handler;
    return handler;
}

bool AbstractHandler::Handle(Command request) {
    if (this->next_handler_) {
        return this->next_handler_->Handle(request);
    }

    return {};
}

AbstractHandler::AbstractHandler(Change ch, FileStorage *file)  : next_handler_(nullptr), ch_(ch), file_(file) {}

bool InsertSymbol::Handle(Command request) {
    if (request == INSERT_SYMBOL){
        InsertChar insertChar(file_, ch_);
        if (insertChar.insertSymbol()){
            ch_ = insertChar.getChange();
            *file_ = insertChar.getFile();
            return true;
        }
        return false;
    }
    else
        return AbstractHandler::Handle(request);
}

bool DeleteSymbol::Handle(Command request) {
    if (request == DELETE_SYMBOL){
        DeleteChar deleteChar(file_, ch_);
        if (deleteChar.deleteSymbol()){
            ch_ = deleteChar.getChange();
            *file_ = deleteChar.getFile();
            return true;
        }
        return false;
    }
    else
        return AbstractHandler::Handle(request);
}

bool selector(Handler &handler, Change ch) {
    const bool result = handler.Handle(ch.cmd);
    if (result)
        return true;
    else
        return false;
}
