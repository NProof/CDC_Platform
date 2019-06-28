#include <limits.h>
#include "../header/Game.h"
#include "gtest/gtest.h"
#include <algorithm>

namespace {
    TEST(GAME, CONSTRCTOR) {
        for(int t = 0; t < 50; t++){
            Game obj;
            int stats[5] = {0,0,0,0};
            int types[17] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            for(int i = 0; i < 32; i++){
                stats[obj.board->chs.at(i).stat]++;
                types[obj.board->chs.at(i).type]++;
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
        }
    }

    TEST(GAME, STR_CONSTRCTOR) {
        std::string str = "kggmmrrnnccpppppKGMRNCPGMRNCPPPP";
        for(int t = 0; t < 50; t++){
            std::random_shuffle(str.begin(), str.end());
            Game obj(str);
            for(int i = 0; i < 32; i++){
                EXPECT_EQ(1, obj.board->chs.at(i).stat);
                EXPECT_EQ(str[i], "XkgmrncpPCNRMGK-"[obj.board->chs.at(i).type]);
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
                if(istat[i] == 1){
                    dark |= tmp;
                    alive &= ~tmp;
                }
                else if(istat[i] == 2){
                    alive |= tmp;
                    dark &= ~tmp;
                }
                else{
                    alive &= ~tmp;
                    dark &= ~tmp;
                }
            }
            Game obj(str, dark, alive);
            for(int i = 0; i < 32; i++){
                EXPECT_EQ(istat[i], obj.board->chs.at(i).stat);
            }
        }
    }
/*
    TEST(GAME, UNIQUENESS) {
        Game obj[2];
        EXPECT_FALSE(std::equal(obj[0].board->chs, obj[0].board->chs+32, obj[1].board->chs));
    }*/
}
