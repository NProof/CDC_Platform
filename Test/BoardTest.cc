#include <limits.h>
#include "../header/Board.h"
#include "gtest/gtest.h"
#include <algorithm>

namespace {
    TEST(CHESS, FILP) {
        Chess * ac[3];
        for(int i=0; i<2; i++){
            ac[i] = new Chess(0, i);
            ac[i]->flip();
            EXPECT_EQ(i, ac[i]->dark ? 0 : 1);
            delete ac[i];
        }
    }

    TEST(BOARD, PICK) {
        Board obj;
        Chess * ch1 = new Chess(0, 0);
        Chess * ch2 = new Chess(1, 0);
        Chess * ptrs[3];
        ptrs[0] = ch1; ptrs[1] = ch2;
        obj.pickDw(1, ch1);
//        EXPECT_EQ(0x2, obj.live);
        obj.pickDw(2, ch2);
//        EXPECT_EQ(0x6, obj.live);
        EXPECT_EQ(ptrs[0], obj.chs.at(1));
        EXPECT_EQ(ptrs[1], obj.chs.at(2));
        Chess * ptr_ch = nullptr;
	EXPECT_EQ(0, obj.pickUp(1, ptr_ch));
//        EXPECT_EQ(0x2, obj.live);
        EXPECT_EQ(ptrs[0], ptr_ch);
        EXPECT_EQ(1, obj.pickUp(2, ptr_ch));
//        EXPECT_EQ(0x2, obj.live);
        EXPECT_EQ(ptrs[0], obj.chs.at(2));
        EXPECT_EQ(ptrs[1], ptr_ch);
        EXPECT_EQ(1, obj.pickDw(2, ptr_ch));
//        EXPECT_EQ(0x2, obj.live);
        EXPECT_EQ(ptrs[0], ptr_ch);
        EXPECT_EQ(ptrs[1], obj.chs.at(2));
    }
}
