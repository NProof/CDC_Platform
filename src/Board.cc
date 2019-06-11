#include "../header/Board.h"
#include <cinttypes>
#include <algorithm>

bool Chess::operator==(const Chess &str) const{
    return this->type == str.type;
}

Board::Board(){
    uint8_t itype[] = {1,2,2,3,3,4,4,5,5,6,6,7,7,7,7,7,8,8,8,8,8,9,9,10,10,11,11,12,12,13,13,14};
    std::random_shuffle(itype, itype + 32);
    for(int i = 0; i < 32; i++){
        this->chs[i].stat = 1;
        this->chs[i].type = itype[i];
    }
}
