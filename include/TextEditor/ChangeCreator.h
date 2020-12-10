#ifndef CHANGE_CREATOR_H
#define CHANGE_CREATOR_H

#include "Message.h"
#include "Mode.h"
#include "Position.h"
#include <string>
#include <vector>

class ChangeCreator {
public:
    ChangeCreator() = default;
    ~ChangeCreator() = default;
    Change virtual CreateChange(Mode &mode,
                                Position &position, std::string &buffer);
    bool virtual CanCreate(Mode &mode,
                           Position &position, std::string &buffer);
    void AddChangeCreator(ChangeCreator*);
private:
    std::vector<ChangeCreator*> changeCreators;
};

class ChangeCreatorInsertSubString : public ChangeCreator {
public:
    Change CreateChange(Mode &mode,
                        Position &position, std::string &buffer) override;
    bool CanCreate(Mode &mode,
                   Position &position, std::string &buffer) override;
};

class ChangeCreatorDeleteSymbol : virtual public ChangeCreator {
public:
    Change CreateChange(Mode &mode,
                        Position &position, std::string &buffer) override;
    bool CanCreate(Mode &mode,
                   Position &position, std::string &buffer) override;
};

class ChangeCreatorDeleteString : virtual public ChangeCreator {
public:
    Change CreateChange(Mode &mode,
                        Position &position, std::string &buffer) override;
    bool CanCreate(Mode &mode,
                   Position &position, std::string &buffer) override;
};

class ChangeCreatorCreateFile : virtual public ChangeCreator {
public:
    Change CreateChange(Mode &mode,
                        Position &position, std::string &buffer) override;
    bool CanCreate(Mode &mode,
                   Position &position, std::string &buffer) override;
};

class ChangeCreatorDeleteFile : virtual public ChangeCreator {
public:
    Change CreateChange(Mode &mode,
                        Position &position, std::string &buffer) override;
    bool CanCreate(Mode &mode,
                   Position &position, std::string &buffer) override;
};

class ChangeCreatorMoveCursor : virtual public ChangeCreator {
public:
    Change CreateChange(Mode &mode,
                        Position &position, std::string &buffer) override;
    bool CanCreate(Mode &mode,
                   Position &position, std::string &buffer) override;
};

#endif // CHANGE_CREATOR_H