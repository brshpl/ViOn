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

    int CreateFile(std::string name) {return -1;};
    int UploadFile(std::string name) {return -1;};
    int DownloadFile(std::string path) {return -1;};
private:
    ChangeCreator mChangeCreator;
    TextEditor editor;
};


#endif //VIONTEXTEDITOR_STARTINTERFACE_H
