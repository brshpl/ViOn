//
// Created by Dashik on 08.12.2020.
//

#include "FileController/EventManager.h"
void Subject::Attach(std::shared_ptr<IObserver> observer) {
    list_observer.push_back(observer);
}
void Subject::Detach(std::shared_ptr<IObserver> observer) {
    list_observer.remove(observer);
}
void Subject::Notify() {
    auto iterator = list_observer.begin();
    amount_of_observers();
    while (iterator != list_observer.end()) {
        (*iterator)->Update(ch);
        ++iterator;
    }
}
int Subject::amount_of_observers() {
    return list_observer.size();
}
Observer::Observer(Subject &subject) :  subject_(subject){
    this->subject_.Attach(std::shared_ptr<IObserver>(this));
}
Change Observer::Update(const Change &ch) {
    ch_ = ch;
    return ch;
}
void Observer::RemoveMeFromTheList() {
    subject_.Detach(std::shared_ptr<IObserver>(this));
}

