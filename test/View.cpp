#include "gtest/gtest.h"
#include "View.h"

TEST(settingText, setText) {
    View view;
    std::vector<Symbol> text = {
            Symbol{'H', 0},
            Symbol{'e', 1},
            Symbol{'l', 2},
            Symbol{'l', 3},
            Symbol{'o', 4},
            Symbol{'\0', 5},
    };
    view.setText(text);

}