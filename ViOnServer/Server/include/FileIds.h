#ifndef VION_CLIENT_GENERATEFILEID_H
#define VION_CLIENT_GENERATEFILEID_H

#include <list>


class FileIds {
public:
    FileIds();

    ssize_t getFileId();

private:
    void GenerateIds();

    std::list<std::size_t> file_ids_;
};


#endif //VION_CLIENT_GENERATEFILEID_H
