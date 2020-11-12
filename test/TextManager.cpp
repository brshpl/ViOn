//
// Created by Dashik on 12.11.2020.
//
#include <gtest/gtest.h>
#include "FileController/TextManager.h"
TEST(CreateFile, ok){
    TextManagerServer server;
    bool is_created = server.createFile();
    ASSERT_EQ(is_created, true);
}
