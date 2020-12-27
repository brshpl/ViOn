#ifndef CHANGE_CREATOR_H
#define CHANGE_CREATOR_H

#include "FileController/Message.h"
#include "Mode.h"
#include <string>
#include <vector>

////
#include <fstream>
extern std::ofstream err;
////

class ChangeCreator {
public:
  ChangeCreator() {
      err << "Construct ChangeCreator " << changeCreators.size() << std::endl;
  };
  ~ChangeCreator() = default;
  Change virtual CreateChange(const Mode &mode, const Position &position,
                              const std::string_view &buffer);
  bool virtual CanCreate(const Mode &mode, const Position &position,
                         const std::string_view &buffer);
  void AddChangeCreator(ChangeCreator *);

private:
  std::vector<ChangeCreator *> changeCreators;
};

class ChangeCreatorInsertSubString : public ChangeCreator {
public:
  Change CreateChange(const Mode &mode, const Position &position,
                      const std::string_view &buffer) override;
  bool CanCreate(const Mode &mode, const Position &position,
                 const std::string_view &buffer) override;
};

class ChangeCreatorDeleteSymbol : public ChangeCreator {
public:
  Change CreateChange(const Mode &mode, const Position &position,
                      const std::string_view &buffer) override;
  bool CanCreate(const Mode &mode, const Position &position,
                 const std::string_view &buffer) override;
};

class ChangeCreatorDeleteString : public ChangeCreator {
public:
  Change CreateChange(const Mode &mode, const Position &position,
                      const std::string_view &buffer) override;
  bool CanCreate(const Mode &mode, const Position &position,
                 const std::string_view &buffer) override;
};

class ChangeCreatorCreateFile : public ChangeCreator {
public:
  Change CreateChange(const Mode &mode, const Position &position,
                      const std::string_view &buffer) override;
  bool CanCreate(const Mode &mode, const Position &position,
                 const std::string_view &buffer) override;
};

class ChangeCreatorDeleteFile : public ChangeCreator {
public:
  Change CreateChange(const Mode &mode, const Position &position,
                      const std::string_view &buffer) override;
  bool CanCreate(const Mode &mode, const Position &position,
                 const std::string_view &buffer) override;
};

class ChangeCreatorMoveCursor : public ChangeCreator {
public:
  Change CreateChange(const Mode &mode, const Position &position,
                      const std::string_view &buffer) override;
  bool CanCreate(const Mode &mode, const Position &position,
                 const std::string_view &buffer) override;
};

#endif // CHANGE_CREATOR_H
