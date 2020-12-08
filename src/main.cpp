#include "ChangeApplier.h"
#include "Parser.h"

int main() {
    struct SymbolState SymbolState0{
        'h', true, 0
    };
    struct SymbolState SymbolState1{
            'e', true, 1
    };
    struct SymbolState SymbolState2{
            'l', true, 2
    };
    struct SymbolState SymbolState3{
            'l', true, 3
    };
    struct SymbolState SymbolState4{
            'o', true, 4
    };
    std::vector<SymbolState> syms;
    syms.push_back(SymbolState0);
    syms.push_back(SymbolState1);
    syms.push_back(SymbolState2);
    syms.push_back(SymbolState3);
    syms.push_back(SymbolState4);
    struct StringState StringState0{
        syms, 0
    };
    std::vector<StringState> strs;
    strs.push_back(StringState0);
    struct FileStorage fileStorage{
        strs, 1, 123, 4, 0
    };
    struct Change ch{
        DELETE_SYMBOL, 1, 4, 0, 3, 'q'
    };
    ChangeApplier applier(ch, fileStorage);
    applier.applyChange();
}