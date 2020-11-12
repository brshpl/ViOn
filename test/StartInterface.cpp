#include <fstream>
#include "gtest/gtest.h"
#include "TextEditor/StartInterface.h"

TEST(createFile, check_creating) {
    ChangeCreator changeCreator;
    TextEditor textEditor;
    StartInterface startInterface(changeCreator, textEditor);
    ASSERT_EQ(startInterface.CreateFile("test_name.txt"), 0);
}
TEST(uploadFile, check_uploading) {
    ChangeCreator changeCreator;
    TextEditor textEditor;
    StartInterface startInterface(changeCreator, textEditor);
    std::ofstream fout;
    fout.open("test_file.txt");
    fout << "Test string";
    fout.close();
    ASSERT_EQ(startInterface.UploadFile("test_file.txt"), 0);
}
TEST(downloadFile, check_downloading) {
    ASSERT_TRUE(false);
}