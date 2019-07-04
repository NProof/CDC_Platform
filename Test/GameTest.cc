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

    TEST(INS, CTR){
        std::map<int, std::string> smap;
        for(int i=0; i<32; i++){
            int x=i/8, y=i%8;
            char tmp[3] = {char(int('a')+x), char(int('1')+y)};
            smap[i] = std::string(tmp);
        }
        for(int i=0; i<32; i++){
            for(int j=0; j<32; j++){
                Ins ins(smap.at(i), smap.at(j));
                EXPECT_EQ(i, ins.src);
                EXPECT_EQ(j, ins.dst);
            }
        }
    }

    TEST(RUN, STEP1){
        Game game("pngpRRpnMGPkCPpPCccmNPPgMNKprrmG");
        game.makeIns(Ins("c7", "c7"));
        game.makeIns(Ins("b5", "b5"));
        game.makeIns(Ins("c4", "c4"));
        game.makeIns(Ins("a3", "a3"));
        game.makeIns(Ins("d3", "d3"));
        game.makeIns(Ins("a6", "a6"));
        game.makeIns(Ins("d8", "d8"));
        game.makeIns(Ins("d1", "d1"));
        game.makeIns(Ins("b1", "b1"));
        game.makeIns(Ins("b8", "b8"));
        game.makeIns(Ins("c2", "c2"));
        game.makeIns(Ins("c5", "c5"));
        game.makeIns(Ins("b3", "b3"));
        game.makeIns(Ins("c4", "c5"));
        game.makeIns(Ins("b4", "b4"));
        game.makeIns(Ins("a3", "b3"));
        game.makeIns(Ins("b5", "b3"));
        game.makeIns(Ins("b4", "b3"));
        game.makeIns(Ins("d2", "d2"));
        game.makeIns(Ins("b2", "b2"));
        game.makeIns(Ins("b2", "c2"));
        game.makeIns(Ins("b3", "b2"));
        game.makeIns(Ins("c3", "c3"));
        game.makeIns(Ins("b2", "c2"));
        game.makeIns(Ins("b1", "b2"));
        game.makeIns(Ins("c3", "c4"));
        game.makeIns(Ins("b2", "b3"));
        game.makeIns(Ins("c5", "b5"));
        game.makeIns(Ins("d7", "d7"));
        game.makeIns(Ins("d7", "c7"));
        game.makeIns(Ins("d8", "d7"));
        game.makeIns(Ins("b7", "b7"));
        game.makeIns(Ins("b8", "b7"));
        game.makeIns(Ins("c7", "b7"));
        game.makeIns(Ins("d6", "d6"));
        game.makeIns(Ins("a7", "a7"));
        game.makeIns(Ins("d7", "d6"));
        game.makeIns(Ins("a4", "a4"));
        game.makeIns(Ins("a2", "a2"));
        game.makeIns(Ins("b7", "b8"));
        game.makeIns(Ins("d5", "d5"));
        game.makeIns(Ins("a7", "b7"));
        game.makeIns(Ins("d6", "d5"));
        game.makeIns(Ins("c6", "c6"));
        game.makeIns(Ins("d5", "c5"));
        game.makeIns(Ins("c4", "c6"));
        game.makeIns(Ins("c5", "c6"));
        game.makeIns(Ins("c8", "c8"));
        game.makeIns(Ins("c1", "c1"));
        game.makeIns(Ins("c2", "c1"));
        game.makeIns(Ins("d3", "c3"));
        game.makeIns(Ins("d4", "d4"));
        game.makeIns(Ins("c6", "c5"));
        game.makeIns(Ins("a4", "b4"));
        game.makeIns(Ins("b3", "b4"));
        game.makeIns(Ins("b5", "b4"));
        game.makeIns(Ins("c5", "c4"));
        game.makeIns(Ins("d4", "d5"));
        game.makeIns(Ins("c4", "b4"));
        game.makeIns(Ins("c8", "c7"));
        game.makeIns(Ins("b4", "b5"));
        game.makeIns(Ins("c7", "c6"));
        game.makeIns(Ins("d2", "d3"));
        game.makeIns(Ins("c1", "d1"));
        game.makeIns(Ins("c3", "c2"));
        game.makeIns(Ins("a1", "a1"));
        game.makeIns(Ins("d3", "c3"));
        game.makeIns(Ins("a1", "b1"));
        game.makeIns(Ins("c3", "b3"));
        game.makeIns(Ins("d5", "d4"));
        game.makeIns(Ins("b5", "b4"));
        game.makeIns(Ins("c6", "c5"));
        game.makeIns(Ins("c2", "c3"));
        game.makeIns(Ins("d1", "d2"));
        game.makeIns(Ins("b4", "c4"));
        game.makeIns(Ins("c5", "c4"));
        game.makeIns(Ins("c3", "c4"));
        game.makeIns(Ins("d4", "c4"));
        game.makeIns(Ins("b6", "b6"));
        game.makeIns(Ins("b7", "b6"));
        game.makeIns(Ins("a6", "b6"));
        game.makeIns(Ins("b8", "b7"));
        game.makeIns(Ins("b6", "b5"));
        game.makeIns(Ins("b7", "b6"));
        game.makeIns(Ins("b5", "c5"));
        game.makeIns(Ins("b6", "b5"));
        game.makeIns(Ins("c5", "c4"));
        game.makeIns(Ins("b5", "b4"));
        game.makeIns(Ins("b3", "a3"));
        game.makeIns(Ins("a2", "a3"));
        game.makeIns(Ins("c4", "c5"));
        game.makeIns(Ins("a5", "a5"));
        game.makeIns(Ins("c5", "c6"));
        game.makeIns(Ins("d2", "d3"));
        game.makeIns(Ins("c6", "d6"));
        game.makeIns(Ins("d3", "d4"));
        game.makeIns(Ins("a5", "a6"));
        game.makeIns(Ins("b4", "b5"));
        game.makeIns(Ins("d6", "d7"));
        game.makeIns(Ins("d4", "d5"));
        game.makeIns(Ins("d7", "c7"));
        game.makeIns(Ins("d5", "d6"));
        game.makeIns(Ins("a6", "a7"));
        game.makeIns(Ins("b5", "b6"));
        game.makeIns(Ins("c7", "c8"));
        game.makeIns(Ins("d6", "c6"));
        game.makeIns(Ins("a8", "a8"));
        game.makeIns(Ins("b6", "a6"));
        game.makeIns(Ins("a7", "a8"));
        game.makeIns(Ins("c6", "c7"));
        game.makeIns(Ins("c8", "b8"));
        game.makeIns(Ins("a6", "a7"));
        game.makeIns(Ins("b8", "b7"));
        game.makeIns(Ins("c7", "b7"));
        game.makeIns(Ins("a8", "b8"));
        game.makeIns(Ins("b7", "b8"));
    }
}
