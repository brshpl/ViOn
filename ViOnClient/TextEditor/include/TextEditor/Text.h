//
// Created by brshpl on 23.12.2020.
//

#ifndef VIONTEXTEDITOR_TEXT_H
#define VIONTEXTEDITOR_TEXT_H

#include <utility>
#include <vector>
#include <string>
#include "Symbol.h"

class Text {
public:
    Text() : text_(20, std::vector<Symbol>(20)) {}
    explicit Text(std::vector<std::vector<Symbol>> text)
    : text_ {std::move(text)} {}

    std::vector<std::vector<Symbol>>& getText();
    std::string getTextStr();

private:
    std::vector<std::vector<Symbol>> text_;
};


#endif //VIONTEXTEDITOR_TEXT_H
