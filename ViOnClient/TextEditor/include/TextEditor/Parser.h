#ifndef VION_PARSER_H
#define VION_PARSER_H

#include "FileController/FileStorage.h"
#include <TextEditor/Symbol.h>
#include <memory>

class Parser{
public:
    explicit Parser(const Change& ch);
    virtual ~Parser() = default;
protected:
    Change ch_;
};

class ParserForEditor : public Parser {
public:
    ParserForEditor(const Change& ch, std::shared_ptr<FileStorage> file);
    ~ParserForEditor() override = default;
    std::vector<std::vector<Symbol>> parse();
private:
    std::shared_ptr<FileStorage> file_;
};

#endif  // VION_PARSER_H
