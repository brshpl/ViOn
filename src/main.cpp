#include <iostream>
#include <FileController/FileStorage.h>
#include <FileController/ChangeApplier.h>
#include <memory>

int main(int argc, char* argv[]) {
    auto position = Position(0);
    Change ch = Change(INSERT_SYMBOL, 1, position, 0, 'q');
    SymbolState s1{'h', true, 1};
    SymbolState s2{'e', true, 2};
    SymbolState s3{'l', true, 3};
    SymbolState s4{'l', true, 4};
    SymbolState s5{'o', true, 5};
    SymbolState s0{'\0', true, 0};
    FileStorage file = FileStorage();
    file.file_id = 1;
    file.symbols_length = 5;
    file.symbols.push_back(s1);
    file.symbols.push_back(s2);
    file.symbols.push_back(s3);
    file.symbols.push_back(s4);
    file.symbols.push_back(s5);
    file.symbols.push_back(s0);
    std::shared_ptr<FileStorage> file_ptr = std::make_shared<FileStorage>(file);
    ChangeApplier applier = ChangeApplier(ch, file_ptr);
    applier.applyChange();
    for (SymbolState s : file_ptr->symbols)
        std::cout << s.symbol << std::endl;
    std::cout << std::endl;
    Change ch1 = Change(DELETE_SYMBOL, 1, position, 5, 'q');
    ChangeApplier applier1 = ChangeApplier(ch1, file_ptr);
    applier1.applyChange();
    for (SymbolState s : file_ptr->symbols)
        if (s.is_visible)
            std::cout << s.symbol << std::endl;
    return 0;
}
