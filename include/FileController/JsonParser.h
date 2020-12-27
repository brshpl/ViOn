#pragma once

#include <string>
#include "Message.h"

class JsonParser {
public:
  static std::string ParseToJson(const Change &ch);
  static Change ParseFromJson(const std::string_view &change);
};
