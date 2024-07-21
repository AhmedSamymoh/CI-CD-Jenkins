#include <iostream>
#include "Calc.h"
#include <gtest/gtest.h>

// TEST(TestCaseName, TestName) {
TEST(SumFunstion, Test1){
    // EXPECT_EQ( expected, actual);
    EXPECT_EQ( 5, sum(2,3));
}

TEST(SubFunstion, Test2){

    EXPECT_EQ( -1, sub(2,3));
}

TEST(SumFunstion, Test3){

    EXPECT_EQ( 5, sub(8,3));
}

int main() {
    //::testing : is a global namespace
    // ::testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}   // main


 