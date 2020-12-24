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
    virtual Change upDate(const Change &ch) = 0;
};

class ISubject{
public:
    virtual ~ISubject(){};
    virtual void attach(std::shared_ptr<IObserver> observer) = 0;
    virtual void detach(std::shared_ptr<IObserver> observer) = 0;
    virtual void notify() = 0;
};

class Subject: public ISubject{
public:
    virtual ~Subject(){}
    void attach(std::shared_ptr<IObserver> observer) override;
    void detach(std::shared_ptr<IObserver> observer) override;
    void notify() override;
private:
    std::list<std::shared_ptr<IObserver>>list_observer;
    Change ch;
};

class Observer: public IObserver{
public:
    Observer(Subject &subject);
    ~Observer() override {}

    Change upDate(const Change &ch);

private:
    Subject &subject_;
};
#endif //VION_EVENTMANAGER_H
