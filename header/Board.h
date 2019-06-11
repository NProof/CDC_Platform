#ifndef BOARD_H_
#define BOARD_H_

#include <cinttypes>
#include <string>

struct Instruction{
    uint8_t dif:2;
    uint8_t src:5;
    uint8_t col:1;
    uint8_t typ:3;
    uint8_t dst:5;
};

struct Chess{
    uint8_t stat:2; // 0:unknown, 1:dark, 2:alive, 3:out_board 
    uint8_t type:4; // index of "XkgmrncpPCNRMGK-", lower case is black chess, upper case is red.
                    // (p > k) & (k > g > m > r > n) & (g > m > r > n > p)
    uint8_t :0;

    bool operator==(const Chess &) const;
};

class Board{
    public:
        //act(Instruction &);
        // [(1) 1,(1) 0] flip dark to alive + (col, type) 
        // [(2) 0,(2) 1] move alive eat alive
        // [(2) 0,(3) 0] move alive to empty
        // [(3) 0,(2) 0] reverse alive to src
        // [(3)-1,(2) 0] reverse alive + (opp's type) to src
        // [(2) 0,(2)-1] reverse alive became dark
        Instruction & ins_gen(src, dst);

        //pick_up(src, dif);
        //pick_dn(dif, dst);

        Board();
        Board(std::string);
        Board(std::string, uint32_t, uint32_t);
    
       	Chess chs[32];
};

#endif
