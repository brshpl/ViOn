//
// Created by Dashik on 12.11.2020.
//
#include <gtest/gtest.h>
#include "FileController/ChangeApplier.h"

bool operator==(const Change &lhs, const Change &rhs){
    return std::tie(lhs.symbol, lhs.newSymbolId, lhs.position.symbolId, lhs.fileId, lhs.cmd) ==
           std::tie(rhs.symbol, rhs.newSymbolId, rhs.position.symbolId, rhs.fileId, rhs.cmd);
}

bool operator==(const FileStorage &lhs, const FileStorage &rhs){
    return std::tie(lhs.file_id, lhs.symbols, lhs.symbols_length) ==
           std::tie(rhs.file_id, rhs.symbols, rhs.symbols_length);
}


bool operator==(const SymbolState &lhs, const SymbolState &rhs){
    return std::tie(lhs.symbol, lhs.is_visible, lhs.id) ==
           std::tie(rhs.symbol, rhs.is_visible, rhs.id);
}

class TestChangeApplier : public ::testing::Test{
protected:
    virtual void SetUp(){
        file  = FileStorage(1);
        applier_right = std::make_unique<ChangeApplier>(ch, std::make_shared<FileStorage>(file));
        applier_wrong = std::make_unique<ChangeApplier>(ch1, std::make_shared<FileStorage>(file));
    }
    virtual void TearDown(){
    }
    Position pos = {0};
    Change ch = Change(INSERT_SYMBOL, 1, pos, 0, 'q');
    Change ch1 = Change(ERROR, 1, pos, 0, 'q');
    FileStorage file;
    std::unique_ptr<ChangeApplier> applier_right;
    std::unique_ptr<ChangeApplier> applier_wrong;
};

TEST_F(TestChangeApplier, applyChange_right_cmd){
    EXPECT_TRUE(applier_right->applyChange());
}

TEST_F(TestChangeApplier, applyChange_wrong_cmd){
    EXPECT_FALSE(applier_wrong->applyChange());
}

TEST_F(TestChangeApplier, getChange){
    EXPECT_EQ(applier_right->getChange(), ch);
}

TEST_F(TestChangeApplier, getFile){
    EXPECT_EQ(applier_right->getFile(), file);
}

