#ifndef GAME_H_
#define GAME_H_

#include "Board.h"
//#include "Player.h"
#include <string>

class Player;

struct Ins{

};

struct StateG{
    int col;
};

class Game{
public:
    Game(std::string = Game::randomStrBoard(), uint32_t = 0xffffffff, uint32_t = 0xffffffff);
    ~Game();
    Game(const Game &) = delete;
  //makeIns(Ins &);
//private:
    //void join(Player &);
    //void left(Player &);

    //std::map<Player *, StateG &> stat_p;
    int turn;
    int col[3] = {0, 0};
    Board * board;
    static std::string randomStrBoard();
};

#endif
