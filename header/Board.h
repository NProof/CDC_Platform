#ifndef BOARD_H_
#define BOARD_H_

#include <cinttypes>
#include <string>

struct Chess{
    uint8_t stat:2; // 0:unknown, 1:dark, 2:alive, 3:out_board 
    uint8_t type:4; // index of "XkgmrncpPCNRMGK-", lower case is black chess, upper case is red.
                    // (p > k) & (k > g > m > r > n) & (g > m > r > n > p)
                    //  k 將 g 士 m 象 r 車  n 馬 c 包 p 卒 K 帥 G 仕 M 相 R ? N 嗎 C 炮 P 兵
                    //   1    2    3    4     5     6    7   14   13   12   11  10   9    8
    uint8_t :0;

    bool operator==(const Chess &) const;
};

class SpaceConfig{
    public:
        static const SpaceConfig * getInstance(int index){
            static const SpaceConfig storage[2] = {SpaceConfig(8,4), SpaceConfig(4,8)};
            return storage + index;
        }

        uint8_t getMajor() const {return _major;}
        uint8_t getMinor() const {return _minor;}

    private:
        SpaceConfig(uint8_t major, uint8_t minor): _major(major), _minor(minor){}
    uint8_t _major:4;
    uint8_t _minor:4;
};

class Board{
    public:
        Board();
        Board(std::string);
        Board(std::string, uint32_t, uint32_t);
        
        SpaceConfig const * cfg_spa;
       	Chess chs[32];
};

bool neighbor(int, int);

/*
bool boom(int x,int y,Board board){ // 這裡你把 int chess[] 改成 Board & board
    int tem;

    if(y>x){
        tem = y;
        y = x;
        x = tem; 
    }
    if(x-y==2&&x%8!=0&&(x-1)%8!=0&&board.chs[x-1].stat!=3){
        return true;
    }
    else if(x-y==16&&board.chs[x-8].stat!=3){
        return true;
    }else return false;
}*/

#endif
