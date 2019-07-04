#ifndef GAME_H_
#define GAME_H_

#include "Board.h"
//#include "Player.h"
#include <string>
#include <stack>

//class Player;

struct Ins{
    Ins(std::string s_src, std::string s_dst);

    // Player * ply;
    int src, dst;
};

struct StatePly{
    int col;
};

class Game{
public:
    Game(std::string = Game::randomStrBoard(), uint32_t = 0xffffffff, uint32_t = 0xffffffff);
    ~Game();
    Game(const Game &) = delete;

    int makeIns(Ins);
//private:
    //void join(Player &);
    //void left(Player &);

    //std::map<Player *, StatePly &> stat_p;
    Board * board;
    std::stack<Chess *> s_ch;
    
    static std::string randomStrBoard();
};

#endif
