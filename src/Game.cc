#include "../header/Game.h"
#include <iostream>
#include <algorithm>

Ins::Ins(std::string s_src, std::string s_dst){
    this->src = 8*(s_src[0]-'a')+(s_src[1]-'1');
    this->dst = 8*(s_dst[0]-'a')+(s_dst[1]-'1');
}

std::string Game::randomStrBoard(){
    std::string str("kggmmrrnnccpppppPPPPPCCNNRRMMGGK");
    std::random_shuffle(str.begin(), str.end());
    return str;
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
    /*for(auto it : this->stat_p){
        left(*it.first);
    }*/
    if(board->chs.size()){
        for(auto it = board->chs.begin(); it != board->chs.end(); it++){
            delete it->second;
        }
        board->chs.clear();
    }
    delete board;
}

/*int Game::makeIns(Ins & ins){
    Chess & actor = this->board->indexOf(ins.src);
    if(ins.src == ins.dst){
        if(!actor.dark){
            std::cerr << "actor isn't dark" << std::endl;
            exit(-1);
        }
        actor.flip();
        return 1;
    }
    else{
        auto it = this->board->chs.find(ins.dst);
        Chess * tmp(nullptr);
        if(it == this->board->chs.end()){
            this->board->pickUp(ins.src, tmp);
            this->board->pickDw(ins.dst, tmp);
            return 3;
        }
        else{
            this->board->pickUp(ins.src, tmp);
            this->board->pickDw(ins.dst, tmp);
            return 4;
        }
    }
}*/

/*void Game::join(Player & ply){
    StateG * s = new StateG();
    this->stat_p.insert(std::pair<Player *, StateG &>(&ply, *s));
    ply.m_state.insert(std::pair<Game *, StateG *>(this, s));
}*/

/*void Game::left(Player & ply){
    StateG * tmp(&this->stat_p.at(&ply));
    ply.m_state.erase(this);
    this->stat_p.erase(&ply);
    delete tmp;
}*/
