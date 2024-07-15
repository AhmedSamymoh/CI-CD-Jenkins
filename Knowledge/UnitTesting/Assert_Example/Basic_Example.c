#include <assert.h>
#include <stdio.h>



void test_add();



// Function to be tested
int add(int a, int b) {
    return a + b;
}

int main() {
    test_add();
    printf("All tests passed!\n");
    return 0;
}



/*********** Tested Code **************/
void test_add() {
    // Arrange
    int a = 2;
    int b = 3;
    int expected = 6;

    // Act
    int result = add(a, b);

    /*
    * assert funtion:
    * it takes a condition as an argument and if the condition is false,
    * the program will terminate with an error message. 
    * Assertion failed: result == expected, line 37
    */
    assert(result == expected);
}
/******************************************/
