#include "../header/Game.h"
#include <iostream>
#include <algorithm>

Game::Game(){
    uint8_t itype[] = {1,2,2,3,3,4,4,5,5,6,6,7,7,7,7,7,8,8,8,8,8,9,9,10,10,11,11,12,12,13,13,14};
    std::random_shuffle(itype, itype + 32);
    board = new Board();
    for(int i = 0; i < 32; i++){
        Chess * ch = new Chess();
        ch->stat = 1;
        ch->type = itype[i];
        board->pickDw(i, ch);
    }
}

Game::Game(std::string str){
    std::map<char, uint8_t> m = {
        {'X',0}, {'k',1}, {'g',2}, {'m',3}, {'r',4}, {'n',5}, {'c',6}, {'p',7}, 
        {'P',8}, {'C',9}, {'N',10}, {'R',11}, {'M',12}, {'G',13}, {'K',14}, {'-',15}
    };
    board = new Board();
    for(int i = 0; i < 32; i++){
        Chess * ch = new Chess();
        ch->stat = 1;
        ch->type = m.at(str[i]);
        board->pickDw(i, ch);
    }
}

Game::Game(std::string str, uint32_t dark, uint32_t alive){
    std::map<char, uint8_t> m = {
        {'X',0}, {'k',1}, {'g',2}, {'m',3}, {'r',4}, {'n',5}, {'c',6}, {'p',7},
        {'P',8}, {'C',9}, {'N',10}, {'R',11}, {'M',12}, {'G',13}, {'K',14}, {'-',15}
    };
    board = new Board();
    uint32_t mask = 0x1;
    for(int i = 0; i < 32; i++){
        Chess * ch = new Chess();
        ch->stat = (dark & mask) ? 1 : ((alive & mask) ? 2 : 3);
        ch->type = m.at(str[i]);
        board->pickDw(i, ch);
        mask <<= 1;
    }
}