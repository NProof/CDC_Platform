#include <limits.h>
#include "../header/Board.h"
#include "gtest/gtest.h"
#include <algorithm>

namespace {
    TEST(BOARD, CONSTRCTOR) {
        for(int t = 0; t < 50; t++){
            Board obj;
            int stats[5] = {0,0,0,0};
            int types[17] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            for(int i = 0; i < 32; i++){
                stats[obj.chs[i].stat]++;
                types[obj.chs[i].type]++;
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

    TEST(BOARD, STR_CONSTRCTOR) {
        std::string str = "kggmmrrnnccpppppKGMRNCPGMRNCPPPP";
        for(int t = 0; t < 50; t++){
            std::random_shuffle(str.begin(), str.end());
            Board obj(str);
            for(int i = 0; i < 32; i++){
                EXPECT_EQ(1, obj.chs[i].stat);
                EXPECT_EQ(str[i], "XkgmrncpPCNRMGK-"[obj.chs[i].type]);
            }
        }
    }

    TEST(BOARD, DETERMINE_CTR) {
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
            Board obj(str, dark, alive);
            for(int i = 0; i < 32; i++){
                EXPECT_EQ(istat[i], obj.chs[i].stat);
            }
        }
    }

    TEST(BOARD, UNIQUENESS) {
        Board obj[2];
        EXPECT_FALSE(std::equal(obj[0].chs, obj[0].chs+32, obj[1].chs));
    }

    TEST(CHESS, STATUS_TRANSFORM) {
        Chess ac[5];
        int8_t dif = 0;
        for(int i=0; i<4; i++){
            ac[i].stat = i;
            ac[i].tran(dif);
            EXPECT_EQ(i, ac[i].stat);
        }
        dif = 1;
        for(int i=0; i<4; i++){
            ac[i].stat = i;
            ac[i].tran(dif);
        }
        EXPECT_EQ(0, ac[0].stat);
        EXPECT_EQ(2, ac[1].stat);
        EXPECT_EQ(3, ac[2].stat);
        EXPECT_EQ(0, ac[3].stat);
        dif = -1;
        for(int i=0; i<4; i++){
            ac[i].stat = i;
            ac[i].tran(dif);
        }
        EXPECT_EQ(0, ac[0].stat);
        EXPECT_EQ(0, ac[1].stat);
        EXPECT_EQ(1, ac[2].stat);
        EXPECT_EQ(2, ac[3].stat);
    }
}
