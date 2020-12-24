//
// Created by Dashik on 08.12.2020.
//

#include "FileController/EventManager.h"
#include <algorithm>
void Subject::attach(std::shared_ptr<IObserver> observer) {
    list_observer.push_back(observer);
}
void Subject::detach(std::shared_ptr<IObserver> observer) {
    list_observer.remove(observer);
}
void Subject::notify() {
    auto iterator = list_observer.begin();
    std::for_each(list_observer.begin(), list_observer.end(), [ch = ch](const std::shared_ptr<IObserver>& observer){observer->upDate(ch);});
}

Observer::Observer(Subject &subject) :  subject_(subject){
    subject_.attach(std::shared_ptr<IObserver>(this));
}
Change Observer::upDate(const Change &ch) {
    return ch;
}
//void Observer::RemoveMeFromTheList() {
//    subject_.detach(std::shared_ptr<IObserver>(this));
//}

