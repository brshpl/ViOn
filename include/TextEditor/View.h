#include <memory>
#include <string>
#include <vector>
#include "Direction.h"
#include "Symbol.h"
#include "Text.h"

class View {
public:
    void moveCursor(Direction direction);
    void listen(int fd_in, int fd_out);
    void insertChar(char ch);
    void deleteChar(char ch);
    void setText(Text &text);
    std::string_view& getStringFromText();
private:

    Text text_;
    void show(const std::string& text);
};
