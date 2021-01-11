#include "TextEditor/Text.h"

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
    return text;
}
