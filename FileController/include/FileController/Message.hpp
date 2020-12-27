#ifndef MESSAGE_H
#define MESSAGE_H

#include "Position.hpp"
#include <cstdlib>

enum Command {
  NOTHING,
  ERROR,
  MOVE_UP,
  MOVE_DOWN,
  MOVE_RIGHT,
  MOVE_LEFT,
  CREATE_FILE,
  DELETE_FILE,
  INSERT_SYMBOL,
  DELETE_STRING,
  DELETE_SYMBOL,
  CHANGE_MODE,
  CLOSE_CONNECT,
  CONNECT_TO_FILE,
  NO_SUCH_FILE_ID
};

struct Change {
  Change() : cmd(NOTHING), fileId(0), position({0, 0}), symbol(0) {}

  Change(Command &_cmd, size_t &_fileId, Position &_position, char &_symbol)
      : cmd(_cmd), fileId(_fileId), position(_position), symbol(_symbol) {}

  Change(const char &_symbol, const Position _position)
      : cmd(INSERT_SYMBOL), fileId(0), position(_position), symbol(_symbol) {}

  ~Change() = default;

  Command cmd;
  size_t fileId;
  size_t newSymbolId;
  Position position;
  char symbol;
};

#endif // MESSAGE_H
