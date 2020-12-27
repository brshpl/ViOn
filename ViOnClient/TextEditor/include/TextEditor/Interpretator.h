
#ifndef INTERPRETATOR_H
#define INTERPRETATOR_H

#include "ChangeCreator.h"
#include "FileController/Message.h"
#include "Mode.h"
#include <string>

class Interpretator {
public:
  Interpretator() : changeCreator(), buffer() {}

  explicit Interpretator(ChangeCreator &_changeCreator)
      : changeCreator(_changeCreator), buffer() {
      buffer.resize(20);
  }

  Change Interpret(int &curChar, const Mode &mode, const Position &position);

private:
  ChangeCreator changeCreator;
  std::string buffer;
};

#endif //  INTERPRETATOR_H