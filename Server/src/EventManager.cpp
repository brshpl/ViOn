#include "EventManager.h"
#include "Parser.h"
#include "FileController/ChangeApplier.h"


void Subject::attach(std::shared_ptr<IObserver> observer) {
    observers_.push_back(observer);
}
void Subject::detach(std::shared_ptr<IObserver> observer) {
    observers_.remove(observer);
}
void Subject::notify(const std::string& change) {
    for (const auto& observer : observers_) {
        observer->update(change);
    }
}
void Subject::setChange(const Change& change) {
    ChangeApplier change_applier(change, file_);
    change_applier.applyChange();

    Change ret_change = change_applier.getChange();
    std::string ret_change_s = ParserToJson(ret_change);

    notify(ret_change_s);
    for (SymbolState s : file_->symbols) {
        if (s.is_visible) {
            std::cout << s.symbol;
        }
    }
    std::cout << std::endl;
}
int Subject::amountOfObservers() {
    return observers_.size();
}

std::shared_ptr<FileStorage> Subject::getFile() {
    return file_;
}


Observer::Observer(Subject &subject, std::shared_ptr<utils::Socket> sock) : subject_(subject), sock_(sock) {
    std::shared_ptr<FileStorage> file = subject_.getFile();

    Position pos = {0};
    Change change = {INSERT_SYMBOL, 0, pos, 0, '\0'};
    sock_->send(ParserToJson(change));
    for (auto symbol : file->symbols) {
        if (symbol.is_visible && symbol.symbol != '\0') {
            change = {INSERT_SYMBOL, 0, pos, symbol.id, symbol.symbol};
            sock_->send(ParserToJson(change));
        }
    }

    this->subject_.attach(std::shared_ptr<IObserver>(this));
}
void Observer::update(const std::string& change) {
    sock_->send(change);
}
void Observer::removeMeFromTheList() {
    subject_.detach(std::shared_ptr<IObserver>(this));
}
void Observer::editFile() {
    Change change;
    do {
        std::string change_str;
        change_str = sock_->recv();
        change = ParserFromJson(change_str);
        if (change.cmd != CLOSE_CONNECT) { subject_.setChange(change); }
        else { sock_->send(change_str); }
    } while (change.cmd != CLOSE_CONNECT);
}
Observer::~Observer() {
}
