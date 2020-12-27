#include <shared_mutex>

#include "EventManager.h"
#include "FileController/JsonParser.h"
#include "FileController/ChangeApplier.h"


static std::shared_mutex mtx;

Subject::Subject(size_t file_id) : file_(std::make_shared<FileStorage>(file_id)) {}
void Subject::attach(IObserver *observer) {
    observers_.push_back(observer);
}
void Subject::detach(IObserver *observer) {
    observers_.remove(observer);
}
void Subject::notify(const std::string& change) {
    for (const auto& observer : observers_) {
        observer->update(change);
    }
}
void Subject::setChange(const Change& change) {
    std::unique_lock<std::shared_mutex> lock(mtx);

    ChangeApplier change_applier(change, file_);
    change_applier.applyChange();

    Change ret_change = change_applier.getChange();

    lock.unlock();

    std::string ret_change_s = JsonParser::ParseToJson(ret_change);

    notify(ret_change_s);

    std::cout << "File №" << file_->file_id << " : <";
    for (SymbolState s : file_->symbols) {
        if (s.is_visible) {
            std::cout << s.symbol;
        }
    }
    std::cout << ">" << std::endl;
}

int Subject::amountOfObservers() {
    return observers_.size();
}

std::shared_ptr<FileStorage> Subject::getFile() {
    return file_;
}


Observer::Observer(Subject &subject, std::shared_ptr<utils::Socket> sock) : subject_(subject), sock_(sock) {
    this->subject_.attach(this);
}
void Observer::update(const std::string& change) {
    sock_->send(change);
}
void Observer::removeMeFromTheList() {
    subject_.detach(this);
}
void Observer::updateFile() {
    std::shared_lock<std::shared_mutex> lock(mtx);

    std::shared_ptr<FileStorage> file = subject_.getFile();

    Position pos;
    for (auto symbol : file->symbols) {
        if (symbol.is_visible && symbol.symbol != '\0') {
            Change change(INSERT_SYMBOL, 0, symbol.id, pos, symbol.symbol);
            sock_->send(JsonParser::ParseToJson(change));
        }
    }
}
void Observer::editFile() {
    Change change;
    do {
        std::string change_str;
        change_str = sock_->recv();
        change = JsonParser::ParseFromJson(change_str);
        if (change.cmd == CLOSE_CONNECT) { sock_->send(change_str); }
        else { subject_.setChange(change); }
    } while (change.cmd != CLOSE_CONNECT);
}
Observer::~Observer() {
}
