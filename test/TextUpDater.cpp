//
// Created by Dashik on 12.11.2020.
//
#include <gtest/gtest.h>
#include <vector>
#include <memory>
#include <FileController/TextUpDater.h>

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

class TestTextUpDater : public ::testing::Test{
protected:
    virtual void SetUp(){
        upDater = TextUpDater(file_ptr, ch);
    }
    virtual void TearDown(){
    }
    Position pos = {0};
    Change ch = Change(INSERT_SYMBOL, 1, pos, 0, 'q');
    FileStorage file = FileStorage(1);
    TextUpDater upDater;
    FileStorage *file_ptr = &file;
};

class TestInsertSymbol : public TestTextUpDater{
protected:
    virtual void SetUp(){
        insertChar = InsertChar(file_ptr, ch);
        insertChar.insertSymbol();
    }
    virtual void TearDown(){
    }
    InsertChar insertChar;
};

class TestDeleteChar : public TestTextUpDater{
protected:
    virtual void SetUp(){
        Change ch1 = Change(DELETE_SYMBOL, 1, pos, 0, 'q');
        deleteChar = DeleteChar(file_ptr, ch1);
        deleteChar.deleteSymbol();
    }
    DeleteChar deleteChar;
};

TEST_F(TestTextUpDater, getChange){
    EXPECT_EQ(upDater.getChange(), ch);
}

TEST_F(TestTextUpDater, getFile){
    EXPECT_EQ(upDater.getFile(), file);
}

TEST_F(TestInsertSymbol, insertSymbol){
    EXPECT_EQ(insertChar.getFile().symbols.begin()->id, insertChar.getChange().newSymbolId);
}

TEST_F(TestDeleteChar, deleteSymbol){
    EXPECT_EQ(deleteChar.getFile().symbols.begin()->is_visible, false);
}







