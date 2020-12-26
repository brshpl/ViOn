#ifndef CHANGE_CREATOR_H
#define CHANGE_CREATOR_H

#include "Message.hpp"
#include "Mode.hpp"
#include "Position.hpp"
#include <string>
#include <vector>

class ChangeCreator {
public:
    ChangeCreator() = default;
    ~ChangeCreator() = default;
    Change virtual CreateChange(const Mode &mode,
                                const Position &position, const std::string_view &buffer);
    bool virtual CanCreate(const Mode &mode,
                           const Position &position, const std::string_view &buffer);
    void AddChangeCreator(ChangeCreator*);
private:
    std::vector<ChangeCreator*> changeCreators;
};

class ChangeCreatorInsertSubString : public ChangeCreator {
public:
    Change CreateChange(const Mode &mode,
                        const Position &position, const std::string_view &buffer) override;
    bool CanCreate(const Mode &mode,
                   const Position &position, const std::string_view &buffer) override;
};

class ChangeCreatorDeleteSymbol : public ChangeCreator {
public:
    Change CreateChange(const Mode &mode,
                        const Position &position, const std::string_view &buffer) override;
    bool CanCreate(const Mode &mode,
                   const Position &position, const std::string_view &buffer) override;
};

class ChangeCreatorDeleteString : public ChangeCreator {
public:
    Change CreateChange(const Mode &mode,
                        const Position &position, const std::string_view &buffer) override;
    bool CanCreate(const Mode &mode,
                   const Position &position, const std::string_view &buffer) override;
};

class ChangeCreatorCreateFile : public ChangeCreator {
public:
    Change CreateChange(const Mode &mode,
                        const Position &position, const std::string_view &buffer) override;
    bool CanCreate(const Mode &mode,
                   const Position &position, const std::string_view &buffer) override;
};

class ChangeCreatorDeleteFile : public ChangeCreator {
public:
    Change CreateChange(const Mode &mode,
                        const Position &position, const std::string_view &buffer) override;
    bool CanCreate(const Mode &mode,
                   const Position &position, const std::string_view &buffer) override;
};

class ChangeCreatorMoveCursor : public ChangeCreator {
public:
    Change CreateChange(const Mode &mode,
                        const Position &position, const std::string_view &buffer) override;
    bool CanCreate(const Mode &mode,
                   const Position &position, const std::string_view &buffer) override;
};

#endif // CHANGE_CREATOR_H
