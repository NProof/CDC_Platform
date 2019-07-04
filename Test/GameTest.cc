#include <limits.h>
#include "../header/Game.h"
#include "gtest/gtest.h"
#include <algorithm>

namespace {
    /*TEST(GAME, PLAYERS){
        Player p1, p2;
        Game game;
        game.join(p1);
        game.join(p2);
        EXPECT_EQ(1, game.stat_p.count(&p1));
        EXPECT_EQ(1, game.stat_p.count(&p2));
    }*/

    TEST(GAME, CONSTRCTOR) {
        for(int t = 0; t < 50; t++){
            Game obj;
            int stats[5] = {0,0,0,0};
            int types[17] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            for(int i = 0; i < 32; i++){
                stats[obj.board->chs.at(i)->dark]++;
                types[obj.board->chs.at(i)->type]++;
            }
            EXPECT_EQ(32, stats[1]);
            EXPECT_EQ(1, types[1]);
            EXPECT_EQ(2, types[2]);
            EXPECT_EQ(2, types[3]);
            EXPECT_EQ(2, types[4]);
            EXPECT_EQ(2, types[5]);
            EXPECT_EQ(2, types[6]);
            EXPECT_EQ(5, types[7]);
            EXPECT_EQ(5, types[8]);
            EXPECT_EQ(2, types[9]);
            EXPECT_EQ(2, types[10]);
            EXPECT_EQ(2, types[11]);
            EXPECT_EQ(2, types[12]);
            EXPECT_EQ(2, types[13]);
            EXPECT_EQ(1, types[14]);
//            EXPECT_EQ(0xffffffff, obj.board->live);
        }
    }

    TEST(GAME, STR_CONSTRCTOR) {
        std::string str = "kggmmrrnnccpppppKGMRNCPGMRNCPPPP";
        for(int t = 0; t < 50; t++){
            std::random_shuffle(str.begin(), str.end());
            Game obj(str);
            for(int i = 0; i < 32; i++){
                EXPECT_EQ(1, obj.board->chs.at(i)->dark);
                EXPECT_EQ(str[i], "XkgmrncpPCNRMGK-"[obj.board->chs.at(i)->type]);
//                EXPECT_EQ(0xffffffff, obj.board->live);
            }
        }
    }

    TEST(GAME, DETERMINE_CTR) {
        std::default_random_engine gen;
        std::uniform_int_distribution<int> dis(1, 3);
        uint8_t istat[33];
        std::string str = "kggmmrrnnccpppppPPPPPCCNNRRMMGGK";
        uint32_t dark, alive, tmp;
        for(int t = 0; t < 50; t++){
            for(int i = 0; i < 32; i++){
                tmp = 0x1 << i;
                istat[i] = dis(gen);
                if(istat[i] == 1){ // dark
                    dark |= tmp;
                    alive |= tmp;
                }
                else if(istat[i] == 2){ // light
                    alive |= tmp;
                    dark &= ~tmp;
                }
                else{ // out board
                    alive &= ~tmp;
                    dark &= ~tmp;
                }
            }
            Game obj(str, alive, dark);
            for(int i = 0; i < 32; i++){
                uint8_t v;
                if(obj.board->chs.count(i)){
                    if(obj.board->chs.at(i)->dark)
                        v = 1;
                    else v = 2;
                }
                else v = 3;
                EXPECT_EQ(istat[i], v);
            }
//            EXPECT_EQ(dark | alive, obj.board->live);
        }
    }

    template <typename Map>
        bool key_compare (Map const &lhs, Map const &rhs) {

        auto pred = [] (decltype(*lhs.begin()) a, decltype(a) b)
                       { return a.second == b.second; };

        return lhs.size() == rhs.size()
            && std::equal(lhs.begin(), lhs.end(), rhs.begin(), pred);
    }

    TEST(GAME, UNIQUENESS) {
        Game * obj[2] = {new Game(), new Game()};
        EXPECT_FALSE((key_compare<std::map<int, Chess *> >(obj[0]->board->chs, obj[1]->board->chs)));
        delete obj[0]; delete obj[1];
    }
}
