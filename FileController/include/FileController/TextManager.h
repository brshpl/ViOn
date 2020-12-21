//
// Created by Dashik on 12.11.2020.
//

#ifndef VION_TEXTMANAGER_H
#define VION_TEXTMANAGER_H
#include "FileController/FileStorage.h"
#include "FileController/Parser.h"
#include <iostream>
#include <vector>


class TextManager{
public:
    TextManager()= default;
    ~TextManager()= default;;
};

class TextManagerClient : public TextManager{
public:
//    TextManagerClient(TextEditor &editor): editor_(editor), file_(0){};
    void setChange(Change ch);
    void setFile(FileStorage file);
    void upDate();
//    TextEditor editor_;
    FileStorage file_;
    Change ch_;
};
#endif //VION_TEXTMANAGER_H
