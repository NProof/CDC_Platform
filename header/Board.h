#ifndef BOARD_H_
#define BOARD_H_

#include <cinttypes>
#include <map>

struct Chess{
    Chess(uint8_t, uint8_t);
    ~Chess();
    Chess(const Chess &);

    int flip();
    uint8_t type:4; // index of "XkgmrncpPCNRMGK-", lower case is black chess, upper case is red.
                    // (p > k) & (k > g > m > r > n) & (g > m > r > n > p)
    uint8_t dark:1; // 0:light, 1:dark

    uint8_t :0;

    bool operator==(const Chess &) const;
};

class Board{
public:
    Board();
    ~Board();
    Board(const Board &) = delete;

    Chess & indexOf(int);
    int pickDw(int, Chess *&);
    int pickUp(int, Chess *&);

//    uint32_t live;
    std::map<int, Chess *> chs;
};

#endif
