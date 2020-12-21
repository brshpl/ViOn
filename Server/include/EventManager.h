#ifndef VION_EVENTMANAGER_H
#define VION_EVENTMANAGER_H

#include <iostream>
#include <list>
#include <string>
#include <memory>

#include "FileController/TextManager.h"
#include "Socket.h"

class IObserver{
public:
    virtual ~IObserver()= default;
    virtual void Update(const std::string& ch) = 0;
};

class ISubject{
public:
    virtual ~ISubject(){};
    virtual void Attach(std::shared_ptr<IObserver> observer) = 0;
    virtual void Detach(std::shared_ptr<IObserver> observer) = 0;
    virtual void Notify(const std::string& ch) = 0;
};

class Subject: public ISubject{
public:
    virtual ~Subject(){}
    void Attach(std::shared_ptr<IObserver> observer) override;
    void Detach(std::shared_ptr<IObserver> observer) override;
    void Notify(const std::string& ch) override;
    int amount_of_observers();
    FileStorage& getFile();
private:
    std::list<std::shared_ptr<IObserver>> list_observer_;
    FileStorage file_;
};

class Observer: public IObserver{
public:
    Observer(Subject &subject, std::shared_ptr<utils::Socket> client);
    ~Observer() override {}

    void Update(const std::string& ch);
    void RemoveMeFromTheList();

private:
    Subject &subject_;
    utils::Socket client_;
};
#endif //VION_EVENTMANAGER_H
