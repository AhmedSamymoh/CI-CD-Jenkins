#include <gtest/gtest.h>

// Function to be tested
int add(int a, int b) {
    return a + b;
}

// Test cases
TEST(AdditionTest, PositiveNumbers) {
    EXPECT_EQ(add(2, 3), 5);
}

TEST(AdditionTest, NegativeAndPositiveNumbers) {
    EXPECT_EQ(add(-1, 1), 0);
}

TEST(AdditionTest, Zeroes) {
    EXPECT_EQ(add(0, 0), 0);
}

TEST(AdditionTest, IncorrectTest) {
    EXPECT_EQ(add(2, 2), 5); // This test is intended to fail
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
