#include <iostream>
#include "Interpretator.h"
#include "Message.h"
#include "Mode.h"
#include "Position.h"
#include <gtest/gtest.h>
#include "Parser.h"


TEST(Parser, AddParser) {
    Parser parser;
    ParseInsertSubString parseInsertSubString;
    parser.AddParser(&parseInsertSubString);
    char testChar = 'x';
    Mode testMode = INSERTATION_MODE;
    Position testPosition = {1, 1};
    std::string testBuffer = "123";
    EXPECT_TRUE(parser.CanParse(testChar, testMode, testPosition, testBuffer));
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
