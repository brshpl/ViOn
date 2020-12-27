#ifndef VION_HANDLER_H
#define VION_HANDLER_H

#include <memory>
#include "Message.h"
#include "FileStorage.h"

class Handler {
public:
    virtual std::shared_ptr<Handler> SetNext(std::shared_ptr<Handler> handler) = 0;
    virtual bool Handle(Command request) = 0;
    virtual ~Handler(){};
};

class AbstractHandler : public Handler {
private:
    std::shared_ptr<Handler> next_handler_;

public:
    AbstractHandler(Change ch, FileStorage *file);
    std::shared_ptr<Handler> SetNext(std::shared_ptr<Handler> handler) override;
    bool Handle(Command request) override;
    ~AbstractHandler(){};

protected:
    Change ch_;
    FileStorage* file_;
};

class InsertSymbol : public AbstractHandler {
public:
    InsertSymbol(Change ch, FileStorage *file) : AbstractHandler(ch, file){};
    ~InsertSymbol(){};
    bool Handle(Command request) override;
};

class DeleteSymbol : public AbstractHandler {
public:
    DeleteSymbol(Change ch, FileStorage *file) : AbstractHandler(ch, file){};
    ~DeleteSymbol(){};
    bool Handle(Command request) override;
};

bool selector(Handler &handler, Change ch);

#endif  // VION_HANDLER_H
