Project Overview
--------------------
- This project consists of two main components: a C++ file containing functions for event reporting and voltage error handling, and a test suite using Google Test to verify the functionality of the error handling logic. Below is a detailed description of each file and their respective functionalities.


Files
---------------
1- cond.cpp
--------------
This file contains two main functions:
- int AEVM_EventReport(void):
      - This function acts as a counter, incrementing a static variable count each time it is called and returning the current count.
      - It does not take any arguments.
- int error(int value):
      - This function handles DC voltage error reporting based on predefined voltage thresholds.
            Input: An integer value representing the current DC voltage.
            Output: An integer representing the status of the voltage error (0 for FAIL, 1 for PASS).
      - The function evaluates the voltage against maximum and minimum voltage thresholds and reports the status using the AEVM_EventReport function.
- Voltage Thresholds
  
      - VMD_DCVM_CFG_MAX_VOLTAGE_THRESHOLD_SCALED_VOLTS: 12 volts
  
      - VMD_DCVM_CFG_MAX_CLEAR_VOLTAGE_THRESHOLD_SCALED_VOLTS: 10 volts
  
      - VMD_DCVM_CFG_MIN_VOLTAGE_THRESHOLD_SCALED_VOLTS: 5 volts
  
      - VMD_DCVM_CFG_MIN_CLEAR_VOLTAGE_THRESHOLD_SCALED_VOLTS: 7 volts
  
- Status Indicators
  
      - AEVM_EVENT_REPORT_ST_FAIL: 0
      - AEVM_EVENT_REPORT_ST_PASS: 1
  
- Test Cases
     - The function checks for over-voltage and under-voltage conditions and reports accordingly:

- Over-voltage:
  
      1- Voltage >= 12 volts: Report FAIL.
      2- 10 volts < Voltage < 12 volts: Report status based on last recorded status.
      3- Voltage <= 10 volts: Report PASS.
- Under-voltage:
-      1- Voltage <= 5 volts: Report FAIL.
-      2- 5 volts < Voltage < 7 volts: Report status based on last recorded status.
-      3- Voltage >= 7 volts: Report PASS.


2- test_cond.cpp
---------------
  - This file contains the test suite for the error function, using Google Test framework.

- Test Cases
    - errorTest, ov:
Tests the over-voltage conditions.

Assertions:

    ASSERT_EQ(0, error(13)); // Voltage >= 12 volts should return 0 (FAIL).
    ASSERT_EQ(0, error(12));
    ASSERT_EQ(0, error(11));
    ASSERT_EQ(1, error(10)); // Voltage <= 10 volts should return 1 (PASS).
    ASSERT_EQ(1, error(9));


- errorTest, ov_nofail:
Tests the condition where voltage is not in a fail state.

Assertion:
      - ASSERT_EQ(1, error(11)); // Voltage between 10 and 12 volts should maintain the last status, in this case, PASS (1).


Main Function

Initializes and runs all tests using Google Test framework.
Usage Instructions
Compile the Project:
Ensure you have Google Test installed.
Compile cond.cpp and test_cond.cpp together with the Google Test library.


Run the Tests:
---------------------
Execute the compiled binary to run all test cases and verify the functionality of the error function.

![image](https://github.com/user-attachments/assets/848901eb-c562-4b76-aa2e-48c5f1946545)


Note:
--------------------
Don't forget to change the name of the folder of the test in the cmakelists file, you can see the file get started witrh Gtest for more understanding:

mine named task :


![image](https://github.com/user-attachments/assets/192c39cc-2c1b-4577-a591-2cceef5a6c60)

