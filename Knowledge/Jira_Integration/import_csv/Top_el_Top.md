# Get the latestest Sprint

This script reads data from a Jira CSV file, finds the highest sprint number, and filters issues related to that sprint, saving them to a new file.

# Importing Libraries

The script imports the csv module, which is part of Python's standard library, to handle CSV file reading and writing.

#  File Path Constants
- INPUT_FILE and OUTPUT_FILE are defined as constants to specify the paths to the input CSV file (jira_all.csv) and the output file (jira_sprint_python_issues.txt).

# Finding the Highest Sprint
1- The find_highest_sprint function opens the input CSV file and iterates through its rows.
2- It skips the header row to start processing data rows directly.
3- For each row, it checks if the sprint field (5th column, index 4) is not empty.
4- It extracts the sprint number by removing the "CCB Sprint " prefix and converts the remaining part to an integer.
5- It keeps track of the highest sprint number encountered during the iteration.
6- The function returns the highest sprint number found.

# Filtering Issues by Sprint
- The filter_issues_by_sprint function opens the input CSV file for reading and the output file for writing.
1- It iterates through the rows of the input file.
2- For each row, it checks if the sprint field is not empty.
3- If the sprint number matches the highest sprint number found earlier, the row is written to the output file.

# Main Function

  The main function coordinates the overall workflow:
    1- It calls find_highest_sprint to determine the highest sprint number.
    2- If no sprint is found, it prints a message and exits.
    3- If a highest sprint is found, it prints the sprint number.
    4- It then calls filter_issues_by_sprint to filter the issues related to the highest sprint and save them to the output file.
    5- Finally, it prints a message indicating that the filtered issues have been saved.

# Entry Point

The if __name__ == "__main__": block ensures that the main function is called when the script is run directly.
This block is a standard Python idiom for making code both importable as a module and executable as a script.
