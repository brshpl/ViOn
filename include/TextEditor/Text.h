//
// Created by brshpl on 23.12.2020.
//

#ifndef VIONTEXTEDITOR_TEXT_H
#define VIONTEXTEDITOR_TEXT_H

#include <utility>
#include <vector>
#include "Symbol.h"

class Text {
public:
    Text() = default;
    explicit Text(std::vector<Symbol> text)
    : text_ {std::move(text)} {}
    std::vector<Symbol> getText();

private:
    std::vector<Symbol> text_;
};


#endif //VIONTEXTEDITOR_TEXT_H
