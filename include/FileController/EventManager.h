//
// Created by Dashik on 05.12.2020.
//
#include <iostream>
#include <list>
#include <string>
#include "TextManager.h"
#ifndef VION_EVENTMANAGER_H
#define VION_EVENTMANAGER_H

class IObserver{
public:
    virtual ~IObserver(){};
    virtual void Update(const Change &ch);
};

class ISubject{
public:
    virtual ~ISubject(){};
    virtual void Attach(IObserver *observer) = 0;
    virtual void Detach(IObserver *observer) = 0;
    virtual void Notify() = 0;
};

class Subject: public ISubject{
public:
    virtual ~Subject(){}
    void Attach(IObserver *observer) override{
        list_observer.push_back(observer);
    }
    void Detach(IObserver *observer) override{
        list_observer.remove(observer);
    }
    void Notify() override{
        std::list<IObserver *>::iterator iterator = list_observer.begin();
        amount_of_observers();
        while (iterator != list_observer.end()) {
            (*iterator)->Update(ch);
            ++iterator;
        }
    }
    int amount_of_observers(){
        return list_observer.size();
    }
private:
    std::list<IObserver *>list_observer;
    Change ch;
};

class Observer: public IObserver{
public:
    Observer(Subject &subject) : subject_(subject) {
        this->subject_.Attach(this);
        this->number_ = Observer::static_number_;
    }
    virtual ~Observer() {}

    void Update(const Change &ch) override {
        ch_ = ch;
    }
    void RemoveMeFromTheList() {
        subject_.Detach(this);
    }

private:
    Change ch_;
    Subject &subject_;
    static int static_number_;
    int number_;
};
#endif //VION_EVENTMANAGER_H
