#include "gtest/gtest.h"
#include "TextEditor.h"

TEST(changeModeAll, changeMode) {
    View view{};
    TextEditor editor(view);
    editor.changeMode(COMMAND_MODE);
    EXPECT_EQ(COMMAND_MODE, editor.getMode());
    editor.changeMode(INSERTATION_MODE);
    EXPECT_EQ(INSERTATION_MODE, editor.getMode());
}

TEST(sendingIsSuccessful, sendChange) {
    try {
        View view{};
        TextEditor editor(view);
        Change change{};
        editor.sendChange(change);
        SUCCEED();
    }
    catch (std::exception const & err) {
        FAIL() << err.what();
    }
}

TEST(modeReturning, getMode) {
    View view{};
    TextEditor editor(view);
    editor.changeMode(COMMAND_MODE);
    Mode mode = editor.getMode();
    EXPECT_EQ(COMMAND_MODE, mode);
}

