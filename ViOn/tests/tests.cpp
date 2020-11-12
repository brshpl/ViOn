#include <iostream>
#include "ChangeCreator.h"
#include "interpretator.h"
#include "message.h"
#include "parser.h"
#include <gtest/gtest.h>

TEST(ChangeCreator, constructor) {
    EXPECT_ANY_THROW(ChangeCreator changeCreator());
}

TEST(ChangeCreator, CreateChange) {
    ChangeCreator changeCreator;
    char curChar = 'a';
    Mode mode = INSERTATION_MODE;
    Position pos = {1, 1};
    std::string str = "string";
    Change chg = changeCreator.CreateChange(curChar, mode, pos, str);
    ChangeInsertSubString expectedChg;
    expectedChg.stringId = pos.stringId;
    expectedChg.cmd = INSERT_SUB_STRING;
    expectedChg.beginSymbolId = pos.symbolId;
    expectedChg.fileId = 0;
    ASSERT_ANY_THROW();
}

TEST(Interpretator, constructor) {
    EXPECT_ANY_THROW(Interpretator inter());
}

TEST(Interpretator, Interpret) {
    ChangeInsertSubString expectedChg;
    Position pos = {1, 1};
    expectedChg.stringId = pos.stringId;
    expectedChg.cmd = INSERT_SUB_STRING;
    expectedChg.beginSymbolId = pos.symbolId;
    expectedChg.fileId = 0;
    Interpretator interpretator;
    char curChar = 'a';
    Change receivedChg = interpretator.Interpret(curChar, INSERTATION_MODE, pos);
    EXPECT_EQ(expectedChg, receivedChg);
}

TEST(Parser, AddParser) {
    ParseInsertSubString src;
    Parser dest;
    dest.AddParser(src);
    ChangeInsertSubString chg;
    Position pos = {1, 1};
    char curChar = 'a';
    Mode mode = INSERTATION_MODE;
    std::string str = "string";
    EXPECT_TRUE(dest.CanParse(curChar, mode, pos, str));
}

TEST(Parser, Parse) {
    ParseInsertSubString src;
    Parser dest;
    dest.AddParser(src);
    ChangeInsertSubString chg;
    Position pos = {1, 1};
    char curChar = 'a';
    Mode mode = INSERTATION_MODE;
    std::string str = "string";
    ChangeInsertSubString expectedChg;
    expectedChg.stringId = pos.stringId;
    expectedChg.cmd = INSERT_SUB_STRING;
    expectedChg.beginSymbolId = pos.symbolId;
    expectedChg.fileId = 0;
    EXPECT_EQ(dest.Parse(curChar, mode, pos, str), expectedChg);
}
