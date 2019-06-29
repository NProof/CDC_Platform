#ifndef BOARD_H_
#define BOARD_H_

#include <cinttypes>
#include <map>

struct Chess{
    Chess(uint8_t, uint8_t);
    ~Chess();
    Chess(const Chess &);

    int tran(int8_t dif);

    uint8_t stat:2; // 0:unknown, 1:dark, 2:alive, 3:out_board 
    uint8_t type:4; // index of "XkgmrncpPCNRMGK-", lower case is black chess, upper case is red.
                    // (p > k) & (k > g > m > r > n) & (g > m > r > n > p)
    uint8_t :0;

    bool operator==(const Chess &) const;
};

class Board{
public:
    Board();
    ~Board();
    Board(const Board &) = delete;

    int pickDw(int, Chess *&);
    int pickUp(int, Chess *&);

//    uint32_t live;
    std::map<int, Chess *> chs;
};

#endif
