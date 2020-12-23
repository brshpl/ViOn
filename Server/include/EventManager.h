#ifndef VION_EVENTMANAGER_H
#define VION_EVENTMANAGER_H


#include <list>
#include <string>
#include <memory>

#include "FileController/TextManager.h"
#include "Socket.h"


class IObserver {
public:
    virtual ~IObserver() = default;
    virtual void Update(const std::string& ch) = 0;
};


class Subject {
public:
    void Attach(std::shared_ptr<IObserver> observer);
    void Detach(std::shared_ptr<IObserver> observer);
    void Notify(const std::string& change);
    void setChange(const Change& change);
    int amountOfObservers();

private:
    std::list<std::shared_ptr<IObserver>> observers_;
    FileStorage file_;
};

class Observer: public IObserver{
public:
    Observer(Subject& subject, std::shared_ptr<utils::Socket> sock);
    ~Observer() override;

    void Update(const std::string& ch) override;
    void RemoveMeFromTheList();

    void editFile();

private:
    Subject& subject_;
    std::shared_ptr<utils::Socket> sock_;
};

#endif  // VION_EVENTMANAGER_H
