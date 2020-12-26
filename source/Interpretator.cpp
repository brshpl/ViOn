#include "Interpretator.hpp"

Change Interpretator::Interpret(char &curChar, const Mode &mode,
                                const Position &position) {
  buffer += curChar;
  Change change = changeCreator.CreateChange(mode, position, buffer);
  if (change.cmd != NOTHING) {
    buffer.clear();
  }
  return change;
}
