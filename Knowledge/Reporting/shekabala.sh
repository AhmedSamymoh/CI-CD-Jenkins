#!/usr/bin/bash

gcc -fprofile-arcs -ftest-coverage -o exec main.c

# Step 2: Run the executable to generate .gcda files
./exec
pwd
gcov -b -o . exec-main.gcda
lcov --capture --directory . --output-file exec.info
genhtml exec.info --output-directory out
