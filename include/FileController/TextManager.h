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
    TextManager()= default;;
};

class TextManagerClient : public TextManager{
public:
//    TextManagerClient(TextEditor &editor);
    void setChange(Change ch);
    void setFile(FileStorage file);
    std::vector<Symbol> upDate();
//    TextEditor editor_;
};
#endif //VION_TEXTMANAGER_H
