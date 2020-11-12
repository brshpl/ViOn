#ifndef VIONTEXTEDITOR_STARTINTERFACE_H
#define VIONTEXTEDITOR_STARTINTERFACE_H

#include <string>
#include "ChangeCreator.h"
#include "TextEditor.h"

class StartInterface {
public:
    StartInterface() = delete;
    StartInterface(ChangeCreator changeCreator, TextEditor textEditor)
        : mChangeCreator {changeCreator}, editor {textEditor} {}

private:
    int CreateFile(std::string name);
    int UploadFile(std::string name);
    int DownloadFile(std::string path);
    ChangeCreator mChangeCreator;
    TextEditor editor;
};


#endif //VIONTEXTEDITOR_STARTINTERFACE_H
