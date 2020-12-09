//
// Created by brshpl on 12.11.2020.
//

#ifndef VIONTEXTEDITOR_INTERPRETATOR_H
#define VIONTEXTEDITOR_INTERPRETATOR_H


#include "Change.h"
#include "TextEditor.h"

class Interpretator {
public:
    Change interpret(char symbol, size_t id, Mode mode);
};


#endif //VIONTEXTEDITOR_INTERPRETATOR_H
