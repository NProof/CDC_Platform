#include <limits.h>
#include "../header/Board.h"
#include "gtest/gtest.h"

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

    TEST(BOARD, UNIQUENESS) {
        Board obj[2];
        EXPECT_FALSE(std::equal(obj[0].chs, obj[0].chs+32, obj[1].chs));
    }
}
