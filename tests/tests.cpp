#include "Interpretator.h"
#include "Message.h"
#include "Mode.h"
#include "Position.h"
#include <gtest/gtest.h>
#include "ChangeCreator.h"

bool operator==(const Change &lhs, const Change &rhs) {
    return std::tie(lhs.position.symbolId,
                    lhs.position.stringId,
                    lhs.str,
                    lhs.fileId,
                    lhs.cmd) == std::tie(rhs.position.symbolId,
                                     rhs.position.stringId,
                                     rhs.str,
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
    std::string testBuffer = "123";
    size_t testFileId = 0;
    Command testCommand = INSERT_SUB_STRING;
    Change expectedChange(testCommand, testFileId, testPosition, testBuffer);
    Change gotChange = parser.CreateChange(testMode, testPosition, testBuffer);
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
    std::string testBuffer = "123";
    size_t testFileId = 0;
    Command testCommand = INSERT_SUB_STRING;
    Change expectedChange(testCommand, testFileId, testPosition, testBuffer);
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
    std::string testBuffer;
    testBuffer.resize(1);
    testBuffer.back() = symbol; // DELETE
    size_t testFileId = 0;
    Command testCommand = DELETE_SYMBOL;
    std::string initBuffer;
    Change expetedChange(testCommand, testFileId, testPosition, initBuffer);
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
    size_t testFileId = 0;
    Command testCommand = DELETE_STRING;
    std::string initBuffer;
    Change expetedChange(testCommand, testFileId, testPosition, initBuffer);
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
    Position testPosition(1, 1);
    std::string testBuffer = "CREATE_FILE";
    Command testCommand = CREATE_FILE;
    size_t testFileId = 0;
    std::string initBuffer;
    Change expectedChange(testCommand, testFileId, testPosition, initBuffer);
    Change gotChange = changeCreatorCreateFile.CreateChange(testMode,
                                                            testPosition, testBuffer);
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
    std::string initBuffer;
    Change expectedChange(testCommand, testFileId, testPosition, initBuffer);
    Change gotChange = changeCreatorDeleteFile.CreateChange(testMode,
                                                            testPosition, testBuffer);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
