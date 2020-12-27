#pragma once

#include <list>
#include <string>
#include <memory>
#include <Socket/Socket.h>
#include <FileController/Message.h>
#include <FileController/FileStorage.h>

#include "FileController/TextManager.h"


class IObserver {
public:
    virtual ~IObserver() = default;
    virtual void update(const std::string& ch) = 0;
};


class Subject {
public:
    Subject() = default;
    explicit Subject(size_t file_id);
    void attach(IObserver *observer);
    void detach(IObserver *observer);
    void notify(const std::string& change);
    void setChange(const Change& change);
    std::shared_ptr<FileStorage> getFile();
    int amountOfObservers();

private:
    std::list<IObserver *> observers_;
    std::shared_ptr<FileStorage> file_;
};

class Observer: public IObserver{
public:
    Observer(Subject& subject, std::shared_ptr<utils::Socket> sock);
    ~Observer() override;

    void update(const std::string& ch) override;
    void removeMeFromTheList();

    void updateFile();
    void editFile();

private:
    Subject& subject_;
    std::shared_ptr<utils::Socket> sock_;
};