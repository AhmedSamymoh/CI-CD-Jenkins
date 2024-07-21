# Jenkins Pipeline Overview
This Jenkins pipeline script automates the process of checking out source code and running a Python script to search for a specific word in a file. Based on the result of the script, the pipeline decides whether to proceed or terminate the build.

# Pipeline Stages
1. Environment Variables
PYTHON_PATH: Specifies the path to the Python executable.
2. Checkout Stage
Purpose: To check out the source code from the configured source control management (SCM) system.
 Steps:
Displays a message indicating the start of the checkout process.
Uses the checkout scm step to retrieve the source code.

3. Run Python Script Stage
Purpose: To execute a Python script (search.py) that searches for the word 'FAILED' in a file (save.txt).
Steps:
Runs the Python script using the bat step, capturing the exit status.
Based on the exit status:
      -      If the status is non-zero, it indicates the word 'FAILED' was not found, and the pipeline continues
      -      If the status is zero, it indicates the word 'FAILED' was found, and the pipeline terminates with an error message


# Summary

- Checkout Stage: Retrieves the source code.
- Run Python Script Stage: Executes the script and makes decisions based on its output.
