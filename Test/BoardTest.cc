#include <limits.h>
#include "../header/Board.h"
#include "gtest/gtest.h"
#include <algorithm>

namespace {
    TEST(CHESS, STATUS_TRANSFORM) {
        Chess * ac[5];
        int8_t dif = 0;
        for(int i=0; i<4; i++){
            ac[i] = new Chess(0, i);
            ac[i]->tran(dif);
            EXPECT_EQ(i, ac[i]->stat);
            delete ac[i];
        }
        dif = 1;
        for(int i=0; i<4; i++){
            ac[i] = new Chess(0, i);
            ac[i]->tran(dif);
        }
        EXPECT_EQ(0, ac[0]->stat);
        EXPECT_EQ(2, ac[1]->stat);
        EXPECT_EQ(3, ac[2]->stat);
        EXPECT_EQ(0, ac[3]->stat);
        for(int i=0; i<4; i++){
            delete ac[i];
        }
        dif = -1;
        for(int i=0; i<4; i++){
            ac[i] = new Chess(0, i);
            ac[i]->tran(dif);
        }
        EXPECT_EQ(0, ac[0]->stat);
        EXPECT_EQ(0, ac[1]->stat);
        EXPECT_EQ(1, ac[2]->stat);
        EXPECT_EQ(2, ac[3]->stat);
        for(int i=0; i<4; i++){
            delete ac[i];
        }
    }

    TEST(CHESS, PICK) {
        Board obj;
        Chess * ch1 = new Chess(0, 0);
        Chess * ch2 = new Chess(1, 0);
        Chess * ptrs[3];
        ptrs[0] = ch1; ptrs[1] = ch2;
        obj.pickDw(1, ch1);
        obj.pickDw(2, ch2);
        EXPECT_EQ(ptrs[0], &obj.chs.at(1));
        EXPECT_EQ(ptrs[1], &obj.chs.at(2));
        Chess * ptr_ch = nullptr;
	EXPECT_EQ(0, obj.pickUp(1, ptr_ch));
        EXPECT_EQ(ptrs[0], ptr_ch);
        EXPECT_EQ(1, obj.pickUp(2, ptr_ch));
        EXPECT_EQ(ptrs[0], &obj.chs.at(2));
        EXPECT_EQ(ptrs[1], ptr_ch);
        EXPECT_EQ(1, obj.pickDw(2, ptr_ch));
        EXPECT_EQ(ptrs[0], ptr_ch);
        EXPECT_EQ(ptrs[1], &obj.chs.at(2));
    }
}
