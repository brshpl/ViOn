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
    virtual void update(const std::string& ch) = 0;
};


class Subject {
public:
    Subject(): file_(std::make_shared<FileStorage>()) {}
    void attach(std::shared_ptr<IObserver> observer);
    void detach(std::shared_ptr<IObserver> observer);
    void notify(const std::string& change);
    void setChange(const Change& change);
    std::shared_ptr<FileStorage> getFile();
    int amountOfObservers();

private:
    std::list<std::shared_ptr<IObserver>> observers_;
    std::shared_ptr<FileStorage> file_;
};

class Observer: public IObserver{
public:
    Observer(Subject& subject, std::shared_ptr<utils::Socket> sock);
    ~Observer() override;

    void update(const std::string& ch) override;
    void removeMeFromTheList();

    void editFile();

private:
    Subject& subject_;
    std::shared_ptr<utils::Socket> sock_;
};

#endif  // VION_EVENTMANAGER_H
