#!/bin/bash
#===================================================================================================
# @Misra.sh:
# This script automates the MISRA C 2012 compliance checking using the open-source cppcheck tool.
# It applies the MISRA C 2012 rules specified in the 'misra.json' configuration file.
# The script performs the following steps:
# 1. Validates that exactly one .c source file is provided .
# 2. Runs cppcheck on the provided source file with MISRA C 2012 rules applied,
#    and saves the output to 'MisraCkOut.txt'.
# 3. Displays the cppcheck output.
# 4. Executes 'CheckMisraC.py' to parse 'MisraCkOut.txt' and determine if any mandatory       
#    rule violations are present. The Jenkins stage will fail if violations are found.        
# @Aurthor : Ahmed Samy
#===================================================================================================
# Usage:
# ./Misra.sh <misra_source_files.txt>
#
# <misra_source_files.txt> :
#   /pathinrepo/src/source_file1.c
#   /pathinrepo/src/source_file2.c
#   /pathinrepo/src/source_file3.c
#
#===================================================================================================


misra_source_files="$1"
# Function to check if the <misra_source_files.txt> file exists and is not empty
source_list_check() {
    if [ ! -f "$misra_source_files" ] || [ ! -s "$misra_source_files" ]; then
        echo "Error: File '$misra_source_files' does not exist or is empty."
        exit 1
    fi
}


# Function to parse the source files listed in <misra_source_files.txt>
parse_and_run_cppcheck() {

    source_list_check 

    # Process each file listed in the source file list
    while IFS= read -r SOURCE_FILE; do

        # Check if the file exists and is not empty
        if [ ! -f "$SOURCE_FILE" ] || [ ! -s "$SOURCE_FILE" ]; then
            echo "Error: File '$SOURCE_FILE' does not exist or is empty."
            continue
        fi
        echo "Misra C Checking ===> : $SOURCE_FILE ====================================="
        # Run cppcheck with the provided source file
        cppcheck --addon="/var/jenkins_home/MisraC/misra.json" --suppress=missingIncludeSystem "$SOURCE_FILE" > MisraCkOut.txt 2>&1

        # Display the cppcheck output
        cat MisraCkOut.txt

        # Run the Python script to parse the cppcheck output
        python3 /var/jenkins_home/MisraC/CheckMisraC.py
        echo "=============> process exit with $? ======================================="

    done < "$misra_source_files"
}

# Main script logic
if [ "$#" -ne 1 ]; then
    echo "Usage: $0 <misra_source_files.txt>"
    exit 1
fi

# Call the function with the provided file
parse_and_run_cppcheck "$1"