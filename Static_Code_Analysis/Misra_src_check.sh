#!/bin/bash
#
# @Misra_src_check.sh
# This script automates the MISRA C 2012 compliance checking using the open-source cppcheck tool.
# It applies the MISRA C 2012 rules specified in the 'misra.json' configuration file.
# The script performs the following steps:
# 1. Validates that exactly one .c source file is provided as an argument.
# 2. Runs cppcheck on the provided source file with MISRA C 2012 rules applied, 
#    and saves the output to 'MisraCkOut.txt'.
# 3. Displays the cppcheck output.
# 4. Executes 'CheckMisraC.py' to parse 'MisraCkOut.txt' and determine if any mandatory 
#    rule violations are present. The Jenkins stage will fail if violations are found.
# @Aurthor : Ahmed Samy
#================================================================================================
# Usage:
# ./Misra_src_check.sh <source_file.c>
#================================================================================================

# Check if the user has provided a .c file as an argument
if [ "$#" -ne 1 ]; then
    echo "Usage: $0 <source_file.c>"
    exit 1
fi

# Get the source file from the argument
SOURCE_FILE="$1"


# Check if the file exists and is not empty
if [ ! -f "$SOURCE_FILE" ] || [ ! -s "$SOURCE_FILE" ]; then
    echo "Error: File '$SOURCE_FILE' does not exist or is empty."
    exit 1
fi

echo "=========================================================================="
echo "Misra C Checking ===> : $SOURCE_FILE "
echo "=========================================================================="

# Run cppcheck with the provided source file
cppcheck --addon="/var/jenkins_home/MisraC/misra.json" --suppress=missingIncludeSystem "$SOURCE_FILE" > MisraCkOut.txt 2>&1 

# Display the cppcheck output
cat MisraCkOut.txt

# Run the Python script
python3 /var/jenkins_home/MisraC/CheckMisraC.py
echo "=============> process exit with $? ======================================="