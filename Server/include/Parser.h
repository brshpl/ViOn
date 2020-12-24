#ifndef SERVER_PARSER_INCLUDE_H_
#define SERVER_PARSER_INCLUDE_H_

#include <string>

#include "FileController/FileStorage.h"


std::string ParserToJson(const Change& ch);
Change ParserFromJson(const std::string& j);

std::string ParserToJson(const FileWorker& worker);
FileWorker ParserFromJsonWorkers(const std::string& worker);

#endif  // SERVER_PARSER_INCLUDE_H_
