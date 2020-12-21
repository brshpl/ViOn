#include "EventManager.h"


void Subject::Attach(std::shared_ptr<IObserver> observer) {
    list_observer_.push_back(observer);
}
void Subject::Detach(std::shared_ptr<IObserver> observer) {
    list_observer_.remove(observer);
}
void Subject::Notify(const std::string& ch) {
    auto iterator = list_observer_.begin();
    amount_of_observers();
    while (iterator != list_observer_.end()) {
        (*iterator)->Update(ch);
        ++iterator;
    }
}
int Subject::amount_of_observers() {
    return list_observer_.size();
}

FileStorage &Subject::getFile() {
    return file_;
}

Observer::Observer(Subject &subject, std::shared_ptr<utils::Socket> client) : subject_(subject){
    this->subject_.Attach(std::shared_ptr<IObserver>(this));
}
void Observer::Update(const std::string& ch) {
    client_.send(ch);
}
void Observer::RemoveMeFromTheList() {
    subject_.Detach(std::shared_ptr<IObserver>(this));
}

