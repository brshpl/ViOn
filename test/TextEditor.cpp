#include "gtest/gtest.h"
#include "TextEditor/TextEditor.h"

TEST(changeMode, checkChange) {
    TextEditor editor;
    editor.changeMode(COMMAND);
    EXPECT_EQ(COMMAND, editor.getMode());
}