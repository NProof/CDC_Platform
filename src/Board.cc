#include "../header/Board.h"

#include <iostream>
#include <map>

Chess::Chess(uint8_t type, uint8_t dark = 1) : type(type), dark(dark) {}

Chess::~Chess(){}

Chess::Chess(const Chess & other) : type(other.type), dark(other.dark) {}

int Chess::flip(){
    dark = dark ? 0 : 1;
    return 0;
}

bool Chess::operator==(const Chess &str) const{
    return this->type == str.type;
}

Board::Board() {}

Board::~Board() {}

Chess & Board::indexOf(int index){
    if(chs.count(index) == 0){
        std::cerr << "board have't chess on " << index << std::endl;
        exit(-1);
    }
    return *chs.at(index);
}

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
