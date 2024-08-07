#!/bin/bash

# Function to check for changes
check_for_changes() {
    echo "Checking for changes..."
    # changes=$(git diff --name-only HEAD~1 HEAD)
    echo "Changed files: $changes"
}

# Function to build the project
build_project() {
    echo "============================================================================================="
    echo "Building source code..."
    echo "From building the Gtest project"
    
    cmake CMakeLists.txt
    make
    ./runTests
    echo "============================================================================================="
    echo "Creating code coverage..."
    mkdir -p CodeCoverage
    cd CodeCoverage
    gcc -fprofile-arcs -ftest-coverage -o coverage main.c ../mul.c ../sum.c
    ./coverage
    cd ..
    echo "============================================================================================="
}

# Function for static code analysis
static_code_analysis() {
    echo "Running Static Code Analysis..."
    echo "============================================================================================="
    echo "Static Code Analysis running..."
    cppcheck --enable=all sum.c
    cppcheck --enable=all mul.c
    echo "============================================================================================="
}

# Function for code coverage analysis
code_coverage() {
    echo "============================================================================================="
    echo "Generating code coverage report..."
    cd CodeCoverage
    gcov -b -o . coverage-main.gcda
    gcov -b -o . coverage-mul.gcda
    gcov -b -o . coverage-sum.gcda

    
    echo "============================================================================================="
    lcov --capture --directory . --output-file coverage.info
    genhtml coverage.info --output-directory out

    cd ..

}

# Function for unit testing
unit_testing() {
    echo "============================================================================================="
    echo "Running unit tests with Google Test..."
    ./sumTest
    echo "============================================================================================="
    ./mulTest
    echo "============================================================================================="
}

# Function for integration testing (Allure)
# integration_testing() {
#     echo "Running integration tests with Allure..."
#     allure serve ./reportallure/
# }

# Function to generate Jira release notes
jira_release_notes() {
    echo "Generating Jira release notes..."
    cd Jira
    chmod 777 ./jira.sh
    ./jira.sh
echo "============================================================================================="
    echo "Jira Release Notes:"
    cat jira_sprint_issues.txt
    echo "============================================================================================="
    cd ..
    cd CodeCoverage/out
    python3 -m http.server 8000
}

# Main script execution
check_for_changes
build_project
static_code_analysis
code_coverage
unit_testing
# integration_testing
jira_release_notes




echo "All stages executed successfully."
