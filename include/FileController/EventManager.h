//
// Created by Dashik on 05.12.2020.
//
#include <iostream>
#include <list>
#include <string>
#include <memory>
#include "TextManager.h"
#ifndef VION_EVENTMANAGER_H
#define VION_EVENTMANAGER_H

class IObserver{
public:
    virtual ~IObserver()= default;
    virtual Change Update(const Change &ch) = 0;
};

class ISubject{
public:
    virtual ~ISubject(){};
    virtual void Attach(std::shared_ptr<IObserver> observer) = 0;
    virtual void Detach(std::shared_ptr<IObserver> observer) = 0;
    virtual void Notify() = 0;
};

class Subject: public ISubject{
public:
    virtual ~Subject(){}
    void Attach(std::shared_ptr<IObserver> observer) override;
    void Detach(std::shared_ptr<IObserver> observer) override;
    void Notify() override;
    int amount_of_observers();
private:
    std::list<std::shared_ptr<IObserver>>list_observer;
    Change ch;
};

class Observer: public IObserver{
public:
    Observer(Subject &subject);
    ~Observer() override {}

    Change Update(const Change &ch);
    void RemoveMeFromTheList();

private:
    Change ch_;
    Subject &subject_;
    int number_;
};
#endif //VION_EVENTMANAGER_H
