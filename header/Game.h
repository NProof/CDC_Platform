#ifndef GAME_H_
#define GAME_H_

#include "../header/Board.h"
#include <string>

struct Ins{

};

class Game{
public:
    Game();
    Game(std::string);
    Game(std::string, uint32_t, uint32_t);
    ~Game();
    Game(const Game &) = delete;
  //makeIns(Ins &);
//pr1ivate:
    int turn;
    int col[3] = {0, 0};
    Board * board;
};

#endif
