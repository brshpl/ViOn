//
// Created by brshpl on 23.12.2020.
//

#include "Text.h"

std::vector<std::vector<Symbol>>& Text::getText() {
    return text_;
}

std::string Text::getTextStr() {
    std::string text;
    for (const auto& str : text_) {
        for (auto symbol : str) {
            text.push_back(symbol.symbol);
        }
    }
    return std::string();
}
