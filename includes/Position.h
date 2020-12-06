#ifndef POSITION_H
#define POSITION_H
struct Position {
    Position(): stringId(0), symbolId(0) {}
    Position(size_t _stringId, size_t _symbolId):
    stringId(_stringId), symbolId(_symbolId) {}
    ~Position() = default;
    size_t  stringId;
    size_t symbolId;
};

#endif
