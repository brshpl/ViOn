#include "Interpretator.h"
#include "Message.h"
#include "Mode.h"
#include "Position.h"
#include <gtest/gtest.h>
#include "ChangeCreator.h"

bool operator==(const Change &lhs, const Change &rhs) {
    return std::tie(lhs.position.symbolId,
                    lhs.position.stringId,
                    lhs.symbol,
                    lhs.fileId,
                    lhs.cmd) == std::tie(rhs.position.symbolId,
                                         rhs.position.stringId,
                                         rhs.symbol,
                                         rhs.fileId,
                                         rhs.cmd);
}

TEST(ChangeCreator, AddChangeCreator) {
    ChangeCreator parser;
    ChangeCreatorInsertSubString parseInsertSubString;
    parser.AddChangeCreator(&parseInsertSubString);
    Mode testMode = INSERTATION_MODE;
    Position testPosition(1, 1);
    std::string testBuffer = "123";
    EXPECT_TRUE(parser.CanCreate(testMode, testPosition, testBuffer));
}

TEST(ChangeCreator, CanCreate) {
    ChangeCreator parser;
    Mode testMode = INSERTATION_MODE;
    Position testPosition(1, 1);
    std::string testBuffer = "123";
    EXPECT_FALSE(parser.CanCreate(testMode, testPosition, testBuffer));
    ChangeCreatorInsertSubString parseInsertSubString;
    parser.AddChangeCreator(&parseInsertSubString);
    EXPECT_TRUE(parser.CanCreate(testMode, testPosition, testBuffer));
}

TEST(ChangeCreator, CreateChange) {
    ChangeCreator parser;
    ChangeCreatorInsertSubString parseInsertSubString;
    parser.AddChangeCreator(&parseInsertSubString);
    Mode testMode = INSERTATION_MODE;
    Position testPosition(1, 1);
    std::string testString = "1";
    size_t testFileId = 0;
    Command testCommand = INSERT_SUB_STRING;
    Change expectedChange(testCommand, testFileId, testPosition, testString[0]);
    Change gotChange = parser.CreateChange(testMode, testPosition, testString);
    EXPECT_EQ(expectedChange, gotChange);
}

TEST(ChangeCreatorInsertSubString, CanCreate) {
    ChangeCreatorInsertSubString parseInsertSubString;
    Mode testMode = INSERTATION_MODE;
    Position testPosition(1, 1);
    std::string testBuffer = "123";
    EXPECT_TRUE(parseInsertSubString.CanCreate(testMode, testPosition, testBuffer));
}

TEST(ChangeCreatorInsertSubString, CreateChange) {
    ChangeCreatorInsertSubString parseInsertSubString;
    Mode testMode = INSERTATION_MODE;
    Position testPosition(1, 1);
    std::string testBuffer = "1";
    size_t testFileId = 0;
    Command testCommand = INSERT_SUB_STRING;
    Change expectedChange(testCommand, testFileId, testPosition, testBuffer.back());
    Change gotChange = parseInsertSubString.CreateChange(testMode, testPosition, testBuffer);
    EXPECT_EQ(expectedChange, gotChange);
}

TEST(ParserDeleteSymbol, CanCreate) {
    Mode testMode = INSERTATION_MODE;
    Position testPosition(1, 1);
    std::string testBuffer;
    testBuffer.resize(1);
    char symbol = 127;
    testBuffer.back() = symbol; // DELETE
    ChangeCreatorDeleteSymbol changeCreatorDeleteSymbol;
    EXPECT_TRUE(changeCreatorDeleteSymbol.CanCreate(testMode,
                                                    testPosition, testBuffer));
    symbol = 8;
    testBuffer.back() = symbol;  // BACKSPACE
    EXPECT_TRUE(changeCreatorDeleteSymbol.CanCreate(testMode,
                                                    testPosition, testBuffer));
}

TEST(ParserDeleteSymbol, CreateChange) {
    Mode testMode = INSERTATION_MODE;
    Position testPosition(1, 1);
    char symbol = 127;
    char expectedSymbol = 0;
    std::string testBuffer;
    testBuffer.resize(1);
    testBuffer.back() = symbol; // DELETE
    size_t testFileId = 0;
    Command testCommand = DELETE_SYMBOL;
    Change expetedChange(testCommand, testFileId, testPosition, expectedSymbol);
    ChangeCreatorDeleteSymbol changeCreatorDeleteSymbol;
    Change gotChange = changeCreatorDeleteSymbol.CreateChange(testMode,
                                                              testPosition, testBuffer);
    EXPECT_EQ(gotChange, expetedChange);
    symbol = 8;
    testBuffer.back() = symbol;  // BACKSPACE
    EXPECT_EQ(gotChange, expetedChange);
}

TEST(ParserDeleteString, CanCreate) {
    ChangeCreatorDeleteString changeCreatorDeleteString;
    Mode testMode = COMMAND_MODE;
    Position testPosition(1, 1);
    std::string testBuffer = "dd";
    EXPECT_TRUE(changeCreatorDeleteString.CanCreate(testMode,
                                                    testPosition, testBuffer));
}

TEST(ParserDeleteString, CreateChange) {
    Mode testMode = COMMAND_MODE;
    Position testPosition(1, 1);
    std::string testBuffer = "dd";
    char expectedSymbol = 0;
    size_t testFileId = 0;
    Command testCommand = DELETE_STRING;
    Change expetedChange(testCommand, testFileId, testPosition, expectedSymbol);
    ChangeCreatorDeleteString changeCreatorDeleteString;
    Change gotChange = changeCreatorDeleteString.CreateChange(testMode,
                                                              testPosition, testBuffer);
    EXPECT_EQ(gotChange, expetedChange);
}

TEST(ParserCreateFile, CanCreate) {
    ChangeCreatorCreateFile changeCreatorCreateFile;
    Mode testMode = COMMAND_MODE;
    Position testPosition(1, 1);
    std::string testBuffer = "CREATE_FILE";
    EXPECT_TRUE(changeCreatorCreateFile.CanCreate(testMode,
                                                  testPosition, testBuffer));
}

TEST(ParserCreateFile, CreateChange) {
    ChangeCreatorCreateFile changeCreatorCreateFile;
    Mode testMode = COMMAND_MODE;
    Position testPosition(0, 0);
    std::string testBuffer = "CREATE_FILE";
    Command testCommand = CREATE_FILE;
    size_t testFileId = 0;
    char expectedSymbol = 0;
    Change expectedChange(testCommand, testFileId, testPosition, expectedSymbol);
    Change gotChange = changeCreatorCreateFile.CreateChange(testMode,
                                                            testPosition, testBuffer);
    EXPECT_EQ(expectedChange, gotChange);
}

TEST(ParserDeleteFile, CanCreate) {
    ChangeCreatorDeleteFile changeCreatorDeleteFile;
    Mode testMode = COMMAND_MODE;
    Position testPosition(1, 1);
    std::string testBuffer = "DELETE_FILE";
    EXPECT_TRUE(changeCreatorDeleteFile.CanCreate(testMode,
                                                  testPosition, testBuffer));
}

TEST(ParserDeleteFile, CreateChange) {
    ChangeCreatorDeleteFile changeCreatorDeleteFile;
    Mode testMode = COMMAND_MODE;
    Position testPosition(1, 1);
    std::string testBuffer = "DELETE_FILE";
    Command testCommand = DELETE_FILE;
    size_t testFileId = 0;
    char expectedChar = 0;
    Change expectedChange(testCommand, testFileId, testPosition, expectedChar);
    Change gotChange = changeCreatorDeleteFile.CreateChange(testMode,
                                                            testPosition, testBuffer);
}

TEST(ChangeCreatorChangeMode, CanCreate) {
    std::string testBuffer = "I";
    Mode testMode = COMMAND_MODE;
    Command testCommand = CHANGE_MODE;
    Position testPosition = {0, 0};
    size_t testFileId = 0;
    char expectedSymbol = 0;
    Change expectedChange(testCommand, testFileId, testPosition, expectedSymbol);
    ChangeCreatorChangeMode changeCreatorChangeMode;
    Change gotChange = changeCreatorChangeMode.CreateChange(testMode, testPosition, testBuffer);
    EXPECT_EQ(gotChange, expectedChange);
    testMode = INSERTATION_MODE;
    testBuffer.back() = 27;
    gotChange = changeCreatorChangeMode.CreateChange(testMode, testPosition, testBuffer);
    EXPECT_EQ(gotChange, expectedChange);
}

TEST(Interpretator, Interpret_Insertation_mode) {
    ChangeCreator changeCreator;
    ChangeCreatorInsertSubString changeCreatorInsertSubString;
    changeCreator.AddChangeCreator(&changeCreatorInsertSubString);
    Interpretator interpretator(changeCreator);
    size_t testFileId = 0;
    Mode testMode = INSERTATION_MODE;
    Position testPosition(0, 0);
    Command testCommand = INSERT_SUB_STRING;
    char testSymblol = '1';
    Change expectedChange(testCommand, testFileId, testPosition, testSymblol);
    Change gotChange = interpretator.Interpret(testSymblol, testMode, testPosition);
    EXPECT_EQ(expectedChange, gotChange);
}

TEST(Interpretator, Interpret_command_mode) {
    ChangeCreator changeCreator;
    ChangeCreatorDeleteString changeCreatorDeleteString;
    changeCreator.AddChangeCreator(&changeCreatorDeleteString);
    Interpretator interpretator(changeCreator);
    size_t testFileId = 0;
    Mode testMode = COMMAND_MODE;
    Position testPosition(0, 0);
    Command testCommand = DELETE_STRING;
    char testSymblol = 'd';
    char gotSymbol = 0;
    Change expectedChange(testCommand, testFileId, testPosition, gotSymbol);
    interpretator.Interpret(testSymblol, testMode, testPosition);
    Change gotChange = interpretator.Interpret(testSymblol, testMode, testPosition);
    EXPECT_EQ(expectedChange, gotChange);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
