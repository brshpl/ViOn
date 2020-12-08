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
    Change Update(const Change &ch);
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
    void Attach(IObserver *observer) override;
    void Detach(IObserver *observer) override;
    void Notify() override;
    int amount_of_observers();
private:
    std::list<IObserver *>list_observer;
    Change ch;
};

class Observer: public IObserver{
public:
    Observer(Subject &subject);
    virtual ~Observer() {}

    Change Update(const Change &ch);
    void RemoveMeFromTheList();

private:
    Change ch_;
    Subject &subject_;
    int number_;
};
#endif //VION_EVENTMANAGER_H
