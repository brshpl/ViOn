#include "gtest/gtest.h"
#include "TextEditor.h"

TEST(changeMode, checkChange) {
    TextEditor editor;
    editor.changeMode(COMMAND_MODE);
    EXPECT_EQ(COMMAND_MODE, editor.getMode());
    editor.changeMode(INSERTATION_MODE);
    EXPECT_EQ(INSERTATION_MODE, editor.getMode());
}