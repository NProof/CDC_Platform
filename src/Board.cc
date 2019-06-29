#include "../header/Board.h"

#include <map>

Chess::Chess(uint8_t type, uint8_t stat) : type(type), stat(stat) {}

Chess::~Chess(){}

Chess::Chess(const Chess & other) : type(other.type), stat(other.stat) {}

int Chess::tran(int8_t dif){
    if(stat == 0)
        return 1;
    int8_t v = stat + dif;
    if(0 < v && v < 4){
        stat = v;
    }
    else 
        stat = 0;
    return 1;
}

bool Chess::operator==(const Chess &str) const{
    return this->type == str.type;
}

/*Chess & Board::indexOf(int index){
    return this->chs.at(index);
}*/

Board::Board() {}

Board::~Board() {}

int Board::pickDw(int pos, Chess *& ptr_ch){
    if(this->chs.count(pos)){
        Chess * tmp(ptr_ch);
        ptr_ch = this->chs.at(pos);
        this->chs.erase(pos);
        this->chs.insert(std::pair<int, Chess *>(pos, tmp));
        return 1;
    }
    else{
//        this->live |= (0x1 << pos);
        this->chs.insert(std::pair<int, Chess *>(pos, ptr_ch));
        ptr_ch = nullptr;
        return 0;
    }
}

int Board::pickUp(int pos, Chess *& ptr_ch){
    if(ptr_ch == nullptr){
//        this->live &= (0x1 << pos);
        ptr_ch = this->chs.at(pos);
        this->chs.erase(pos);
        return 0;
    }
    else{
        Chess * tmp = ptr_ch;
        ptr_ch = this->chs.at(pos);
        this->chs.erase(pos);
        this->chs.insert(std::pair<int, Chess *>(pos, tmp));
        return 1;
    }
}
