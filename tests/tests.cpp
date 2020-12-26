#include "ChangeCreator.hpp"
#include "Interpretator.hpp"
#include "JsonParser.hpp"
#include "Message.hpp"
#include "Mode.hpp"
#include "Position.hpp"
#include "json.hpp"
#include <gtest/gtest.h>

bool operator==(const Change &lhs, const Change &rhs) {
  return std::tie(lhs.position.symbolId, lhs.position.stringId, lhs.symbol,
                  lhs.fileId, lhs.cmd) ==
         std::tie(rhs.position.symbolId, rhs.position.stringId, rhs.symbol,
                  rhs.fileId, rhs.cmd);
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
  Command testCommand = INSERT_SYMBOL;
  Change expectedChange(testCommand, testFileId, testPosition, testString[0]);
  Change gotChange = parser.CreateChange(testMode, testPosition, testString);
  EXPECT_EQ(expectedChange, gotChange);
}

TEST(ChangeCreatorInsertSubString, CanCreate) {
  ChangeCreatorInsertSubString parseInsertSubString;
  Mode testMode = INSERTATION_MODE;
  Position testPosition(1, 1);
  std::string testBuffer = "123";
  EXPECT_TRUE(
      parseInsertSubString.CanCreate(testMode, testPosition, testBuffer));
}

TEST(ChangeCreatorInsertSubString, CreateChange) {
  ChangeCreatorInsertSubString parseInsertSubString;
  Mode testMode = INSERTATION_MODE;
  Position testPosition(1, 1);
  std::string testBuffer = "1";
  size_t testFileId = 0;
  Command testCommand = INSERT_SYMBOL;
  Change expectedChange(testCommand, testFileId, testPosition,
                        testBuffer.back());
  Change gotChange =
      parseInsertSubString.CreateChange(testMode, testPosition, testBuffer);
  EXPECT_EQ(expectedChange, gotChange);
}

TEST(ChangeCreatorDeleteSymbol, CanCreate) {
  Mode testMode = INSERTATION_MODE;
  Position testPosition(1, 1);
  std::string testBuffer;
  testBuffer.resize(1);
  char symbol = 127;
  testBuffer.back() = symbol; // DELETE
  ChangeCreatorDeleteSymbol changeCreatorDeleteSymbol;
  EXPECT_TRUE(
      changeCreatorDeleteSymbol.CanCreate(testMode, testPosition, testBuffer));
  symbol = 8;
  testBuffer.back() = symbol; // BACKSPACE
  EXPECT_TRUE(
      changeCreatorDeleteSymbol.CanCreate(testMode, testPosition, testBuffer));
}

TEST(ChangeCreatorDeleteSymbol, CreateChange) {
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
  Change gotChange = changeCreatorDeleteSymbol.CreateChange(
      testMode, testPosition, testBuffer);
  EXPECT_EQ(gotChange, expetedChange);
  symbol = 8;
  testBuffer.back() = symbol; // BACKSPACE
  EXPECT_EQ(gotChange, expetedChange);
}

TEST(ChangeCreatorDeleteString, CanCreate) {
  ChangeCreatorDeleteString changeCreatorDeleteString;
  Mode testMode = COMMAND_MODE;
  Position testPosition(1, 1);
  std::string testBuffer = "dd";
  EXPECT_TRUE(
      changeCreatorDeleteString.CanCreate(testMode, testPosition, testBuffer));
}

TEST(ChangeCreatorDeleteString, CreateChange) {
  Mode testMode = COMMAND_MODE;
  Position testPosition(1, 1);
  std::string testBuffer = "dd";
  char expectedSymbol = 0;
  size_t testFileId = 0;
  Command testCommand = DELETE_STRING;
  Change expetedChange(testCommand, testFileId, testPosition, expectedSymbol);
  ChangeCreatorDeleteString changeCreatorDeleteString;
  Change gotChange = changeCreatorDeleteString.CreateChange(
      testMode, testPosition, testBuffer);
  EXPECT_EQ(gotChange, expetedChange);
}

TEST(ChangeCreatorCreateFile, CanCreate) {
  ChangeCreatorCreateFile changeCreatorCreateFile;
  Mode testMode = COMMAND_MODE;
  Position testPosition(1, 1);
  std::string testBuffer = "CREATE_FILE";
  EXPECT_TRUE(
      changeCreatorCreateFile.CanCreate(testMode, testPosition, testBuffer));
}

TEST(ChangeCreatorCreateFile, CreateChange) {
  ChangeCreatorCreateFile changeCreatorCreateFile;
  Mode testMode = COMMAND_MODE;
  Position testPosition(0, 0);
  std::string testBuffer = "CREATE_FILE";
  Command testCommand = CREATE_FILE;
  size_t testFileId = 0;
  char expectedSymbol = 0;
  Change expectedChange(testCommand, testFileId, testPosition, expectedSymbol);
  Change gotChange =
      changeCreatorCreateFile.CreateChange(testMode, testPosition, testBuffer);
  EXPECT_EQ(expectedChange, gotChange);
}

TEST(ChangeCreatorDeleteFile, CanCreate) {
  ChangeCreatorDeleteFile changeCreatorDeleteFile;
  Mode testMode = COMMAND_MODE;
  Position testPosition(1, 1);
  std::string testBuffer = "DELETE_FILE";
  EXPECT_TRUE(
      changeCreatorDeleteFile.CanCreate(testMode, testPosition, testBuffer));
}

TEST(ChangeCreatorDeleteFile, CreateChange) {
  ChangeCreatorDeleteFile changeCreatorDeleteFile;
  Mode testMode = COMMAND_MODE;
  Position testPosition(1, 1);
  std::string testBuffer = "DELETE_FILE";
  Command testCommand = DELETE_FILE;
  size_t testFileId = 0;
  char expectedChar = 0;
  Change expectedChange(testCommand, testFileId, testPosition, expectedChar);
  Change gotChange =
      changeCreatorDeleteFile.CreateChange(testMode, testPosition, testBuffer);
}

TEST(ChangeCreatorMoveCursor, CanCreate) {
  std::string arrow = {27, '[', 'A'}; // Вверх
  Command testCommand = MOVE_UP;
  Change expectedChange;
  expectedChange.cmd = testCommand;
  ChangeCreatorMoveCursor changeCreatorMoveCursor;
  Mode testMode = COMMAND_MODE;
  Position testPosition = {0, 0};
  EXPECT_TRUE(changeCreatorMoveCursor.CanCreate(testMode, testPosition, arrow));
  arrow[2] = 'B'; // Вниз
  EXPECT_TRUE(changeCreatorMoveCursor.CanCreate(testMode, testPosition, arrow));
  arrow[2] = 'C'; // Вправо
  EXPECT_TRUE(changeCreatorMoveCursor.CanCreate(testMode, testPosition, arrow));
  arrow[2] = 'D'; // Влево
  EXPECT_TRUE(changeCreatorMoveCursor.CanCreate(testMode, testPosition, arrow));
}

TEST(ChangeCreatorMoveCursor, CreateChange) {
  std::string arrow = {27, '[', 'A'}; // Вверх
  Command testCommand = MOVE_UP;
  Change expectedChange;
  expectedChange.cmd = testCommand;
  ChangeCreatorMoveCursor changeCreatorMoveCursor;
  Mode testMode = COMMAND_MODE;
  Position testPosition = {0, 0};
  Change gotChange =
      changeCreatorMoveCursor.CreateChange(testMode, testPosition, arrow);
  EXPECT_EQ(expectedChange, gotChange);
  arrow[2] = 'B'; // Вниз
  expectedChange.cmd = MOVE_DOWN;
  gotChange =
      changeCreatorMoveCursor.CreateChange(testMode, testPosition, arrow);
  EXPECT_EQ(expectedChange, gotChange);
  arrow[2] = 'C'; // Вправо
  expectedChange.cmd = MOVE_RIGHT;
  gotChange =
      changeCreatorMoveCursor.CreateChange(testMode, testPosition, arrow);
  EXPECT_EQ(expectedChange, gotChange);
  arrow[2] = 'D'; // Влево
  expectedChange.cmd = MOVE_LEFT;
  gotChange =
      changeCreatorMoveCursor.CreateChange(testMode, testPosition, arrow);
  EXPECT_EQ(expectedChange, gotChange);
}

TEST(Interpretator, Interpret_Insertation_mode) {
  ChangeCreator changeCreator;
  ChangeCreatorInsertSubString changeCreatorInsertSubString;
  changeCreator.AddChangeCreator(&changeCreatorInsertSubString);
  Interpretator interpretator(changeCreator);
  size_t testFileId = 0;
  Mode testMode = INSERTATION_MODE;
  Position testPosition(0, 0);
  Command testCommand = INSERT_SYMBOL;
  char testSymblol = '1';
  Change expectedChange(testCommand, testFileId, testPosition, testSymblol);
  Change gotChange =
      interpretator.Interpret(testSymblol, testMode, testPosition);
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
  Change gotChange =
      interpretator.Interpret(testSymblol, testMode, testPosition);
  EXPECT_EQ(expectedChange, gotChange);
}

TEST(JsonParser, ParseToJson) {
  Change testChg('a', {0, 0});
  std::string gotString = JsonParser::ParseToJson(testChg);
  nlohmann::json expectedJson =
      nlohmann::json::object({{"cmd", testChg.cmd},
                              {"fileId", testChg.fileId},
                              {"position",
                               {{"symbolId", testChg.position.symbolId},
                                {"stringId", testChg.position.stringId}}},
                              {"symbol", testChg.symbol}});
  std::string expectedString = expectedJson.dump();
  EXPECT_EQ(gotString, expectedString);
}

TEST(JsonParser, ParseFromJson) {
  Change expectedChange('a', {0, 0});
  nlohmann::json expectedJson = nlohmann::json::object(
      {{"cmd", expectedChange.cmd},
       {"fileId", expectedChange.fileId},
       {"position",
        {{"symbolId", expectedChange.position.symbolId},
         {"stringId", expectedChange.position.stringId}}},
       {"symbol", expectedChange.symbol}});
  std::string str = expectedJson.dump();
  Change gotChange = JsonParser::ParseFromJson(str);
  EXPECT_EQ(expectedChange, gotChange);
}

TEST(JsonParser, FunctionsCompatibility) {
  Change expectedChange('a', {0, 0});
  std::string testStr = JsonParser::ParseToJson(expectedChange);
  Change gotChange = JsonParser::ParseFromJson(testStr);
  EXPECT_EQ(expectedChange, gotChange);
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
