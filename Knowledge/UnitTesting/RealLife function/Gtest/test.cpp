#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "cond.cpp"

TEST(errorTest, ov) { 
    ASSERT_EQ(0, error(13));
ASSERT_EQ(0, error(12));
ASSERT_EQ(0, error(11));
ASSERT_EQ(1, error(10));
ASSERT_EQ(1, error(9));
   
}
TEST(errorTest, ov_nofail) { 
    ASSERT_EQ(1, error(11));

 
}
int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
