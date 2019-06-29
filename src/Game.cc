#include "../header/Game.h"
#include <iostream>
#include <algorithm>

Game::Game() : turn(0) {
    uint8_t itype[] = {1,2,2,3,3,4,4,5,5,6,6,7,7,7,7,7,8,8,8,8,8,9,9,10,10,11,11,12,12,13,13,14};
    std::random_shuffle(itype, itype + 32);
    board = new Board();
    for(int i = 0; i < 32; i++){
        Chess * ch = new Chess(itype[i], 1);
        board->pickDw(i, ch);
    }
}

Game::Game(std::string str) : turn(0) {
    std::map<char, uint8_t> m = {
        {'X',0}, {'k',1}, {'g',2}, {'m',3}, {'r',4}, {'n',5}, {'c',6}, {'p',7}, 
        {'P',8}, {'C',9}, {'N',10}, {'R',11}, {'M',12}, {'G',13}, {'K',14}, {'-',15}
    };
    board = new Board();
    for(int i = 0; i < 32; i++){
        Chess * ch = new Chess(m.at(str[i]), 1);
        board->pickDw(i, ch);
    }
}

Game::Game(std::string str, uint32_t alive, uint32_t dark) : turn(0) {
    std::map<char, uint8_t> m = {
        {'X',0}, {'k',1}, {'g',2}, {'m',3}, {'r',4}, {'n',5}, {'c',6}, {'p',7},
        {'P',8}, {'C',9}, {'N',10}, {'R',11}, {'M',12}, {'G',13}, {'K',14}, {'-',15}
    };
    board = new Board();
    uint32_t mask = 0x1;
    for(int i = 0; i < 32; i++){
        if(alive & mask){
            Chess * ch = new Chess(m.at(str[i]), (dark & mask) ? 1 : 0);
            board->pickDw(i, ch);
        }
        mask <<= 1;
    }
}

Game::~Game(){
    if(board->chs.size()){
        for(auto it = board->chs.begin(); it != board->chs.end(); it++){
            delete it->second;
        }
        board->chs.clear();
    }
    delete board;
}
