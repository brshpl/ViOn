#include <iostream>
#include "Position.h"
#include "Mode.h"
#include "Message.h"
#include "ChangeCreator.h"
#include "Interpretator.h"
#include "ChangeCreator.h"

void foo(Change& chg) {

}

int main() {
    Change chg;
    chg.fileId = 1;
    chg.stringId = 2;
    chg.symbolId = 3;
    foo(chg);
    return 0;
}
