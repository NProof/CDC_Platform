#ifndef GAME_H_
#define GAME_H_

#include "Board.h"
#include "Player.h"
#include <string>

class Player;

struct Ins{

};

struct StateG{
    int col;
};

class Game{
public:
    Game();
//    Game(std::string);
    Game(std::string, uint32_t = 0xffffffff, uint32_t = 0xffffffff);
    ~Game();
    Game(const Game &) = delete;
  //makeIns(Ins &);
//pr1ivate:
    Player * players[3];
    int turn;
    int col[3] = {0, 0};
    Board * board;
};

#endif
