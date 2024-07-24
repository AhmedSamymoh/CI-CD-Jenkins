#include <gtest/gtest.h>

// Function to be tested
int multiply(int a, int b) {
    return a * b;
}

// Test cases
TEST(MultiplicationTest, PositiveNumbers) {
    EXPECT_EQ(multiply(2, 3), 6);
}

TEST(MultiplicationTest, NegativeAndPositiveNumbers) {
    EXPECT_EQ(multiply(-1, 1), -1);
}

TEST(MultiplicationTest, Zeroes) {
    EXPECT_EQ(multiply(0, 0), 0);
}

TEST(MultiplicationTest, IncorrectTest) {
    EXPECT_EQ(multiply(2, 2), 5); // This test is intended to fail
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
