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
    ChangeApplier change_applier(change, std::make_unique<FileStorage>(file_));
    change_applier.applyChange();

    Change ret_change = change_applier.getChange();
    std::string ret_change_s = ParserToJson(ret_change);

    notify(ret_change_s);
}
int Subject::amountOfObservers() {
    return observers_.size();
}


Observer::Observer(Subject &subject, std::shared_ptr<utils::Socket> sock) : subject_(subject), sock_(sock) {
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
