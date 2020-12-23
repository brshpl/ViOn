#include "EventManager.h"
#include "Parser.h"
#include "FileController/ChangeApplier.h"


void Subject::Attach(std::shared_ptr<IObserver> observer) {
    observers_.push_back(observer);
}
void Subject::Detach(std::shared_ptr<IObserver> observer) {
    observers_.remove(observer);
}
void Subject::Notify(const std::string& change) {
    for (const auto& observer : observers_) {
        observer->Update(change);
    }
    /*auto iterator = observers_.begin();
    amountOfObservers();
    while (iterator != observers_.end()) {
        (*iterator)->Update(change_);
        ++iterator;
    }*/
}
void Subject::setChange(const Change& change) {
    ChangeApplier change_applier(change, std::make_unique<FileStorage>(file_));
    change_applier.applyChange();

    Change ret_change = change_applier.getChange();
    std::string ret_change_s = ParserToJson(ret_change);

    Notify(ret_change_s);
}
int Subject::amountOfObservers() {
    return observers_.size();
}


Observer::Observer(Subject &subject, std::shared_ptr<utils::Socket> sock) : subject_(subject), sock_(sock) {
    this->subject_.Attach(std::shared_ptr<IObserver>(this));
}
void Observer::Update(const std::string& change) {
    sock_->send(change);
}
void Observer::RemoveMeFromTheList() {
    subject_.Detach(std::shared_ptr<IObserver>(this));
}
void Observer::editFile() {
    Change change;
    do {
        std::string change_str;
        change_str = sock_->recv();
        change = ParserFromJson(change_str);
        subject_.setChange(change);
    } while (change.cmd != CLOSE_CONNECT);
}
Observer::~Observer() {
    RemoveMeFromTheList();
}
