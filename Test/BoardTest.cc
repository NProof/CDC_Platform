#include <limits.h>
#include "../header/Board.h"
#include "gtest/gtest.h"
#include <algorithm>

using namespace std;

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

    TEST(CONFIG, INSTANCE) {
        const SpaceConfig * ptr_0 = SpaceConfig::getInstance(0);
        const SpaceConfig * ptr_1 = SpaceConfig::getInstance(1);
        EXPECT_EQ(8, ptr_0->getMajor());
        EXPECT_EQ(4, ptr_0->getMinor());
        EXPECT_EQ(4, ptr_1->getMajor());
        EXPECT_EQ(8, ptr_1->getMinor());

    }

 //  1 2 3 4 5 6 7 8 

    TEST(FUN, NEIGHBOR) {
        /*
        for(int i=0; i<8; i++){
            EXPECT_TRUE(neighbor(4*i, 1+4*i));
            EXPECT_TRUE(neighbor(1+4*i, 2+4*i));
            EXPECT_TRUE(neighbor(2+4*i, 3+4*i));
        }
        for(int j=0; j<4; j++){
            EXPECT_TRUE(neighbor(j, 4+j));
            EXPECT_TRUE(neighbor(4+j, 8+j));
            EXPECT_TRUE(neighbor(8+j, 12+j));
            EXPECT_TRUE(neighbor(12+j, 16+j));
            EXPECT_TRUE(neighbor(16+j, 20+j));
            EXPECT_TRUE(neighbor(20+j, 24+j));
            EXPECT_TRUE(neighbor(24+j, 28+j));
        }*/
        Board obj;
        set<set<int> > truepair;
        int pair[3];
        for(int i=0; i<8; i++){
            pair[0] = i; pair[1] = 8+i;
            truepair.insert(set<int>(pair, pair+2));
            pair[0] = 8+i; pair[1] = 16+i;
            truepair.insert(set<int>(pair, pair+2));
            pair[0] = 16+i; pair[1] = 24+i;
            truepair.insert(set<int>(pair, pair+2));
        }
        for(int j=0; j<4; j++){
            pair[0] = 0+8*j; pair[1] = 1+8*j;
            truepair.insert(set<int>(pair, pair+2));
            pair[0] = 1+8*j; pair[1] = 2+8*j;
            truepair.insert(set<int>(pair, pair+2));
            pair[0] = 2+8*j; pair[1] = 3+8*j;
            truepair.insert(set<int>(pair, pair+2));
            pair[0] = 3+8*j; pair[1] = 4+8*j;
            truepair.insert(set<int>(pair, pair+2));
            pair[0] = 4+8*j; pair[1] = 5+8*j;
            truepair.insert(set<int>(pair, pair+2));
            pair[0] = 5+8*j; pair[1] = 6+8*j;
            truepair.insert(set<int>(pair, pair+2));
            pair[0] = 6+8*j; pair[1] = 7+8*j;
            truepair.insert(set<int>(pair, pair+2));
        }
        for(int i = 0; i < 32; i++){
            for(int j = 0 ; j < 32; j++) {
                pair[0] = i; pair[1] = j;
                EXPECT_EQ(truepair.count(set<int>(pair, pair+2)), obj.neighbor(i, j));
            }
        }
    }
}
