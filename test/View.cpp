#include "gtest/gtest.h"
#include "View.h"

TEST(settingText, setText) {
    View view;
    std::vector<Symbol> text {
            Symbol{'H', 0},
            Symbol{'e', 1},
            Symbol{'l', 2},
            Symbol{'l', 3},
            Symbol{'o', 4},
            Symbol{'\0', 5},
    };
    Text testText{text};
    view.setText(testText);
    std::string eqlStr = "Hello";
    eqlStr.insert(eqlStr.length(), 1, '\0');
    EXPECT_EQ(view.getStringFromText(), eqlStr);
}