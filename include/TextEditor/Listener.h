#ifndef VIONTEXTEDITOR_LISTENER_H
#define VIONTEXTEDITOR_LISTENER_H

#include "Interpretator.h"
#include "Change.h"

class Listener {
public:
    Change listen(int fd);
private:
    Interpretator interpretator;
};


#endif //VIONTEXTEDITOR_LISTENER_H
