# Jira Data Extraction :

This script is designed to extract data from a Jira project and save it as a CSV file. It makes use of the Jira REST API and the jq JSON processor.

![image](https://github.com/user-attachments/assets/4d99af2f-cd2a-472e-9863-34cc0cb5a1fb)

# Prerequisites
  - Ensure that curl is installed and available in your system's PATH.
  - Install jq and ensure it is available in C:\Program Files\jq\jq.exe.


# Script Overview
  This script performs the following steps:

1- Set Jira Credentials and Endpoint: Sets the Jira user, API token, and URL for the Jira project.
2- Set Output File: Specifies the output CSV file where the data will be saved.
3- Make API Request: Uses curl to send a GET request to the Jira API and saves the response to a file.
4- Check for Errors: Uses jq to check if the response contains any errors.
5- Process JSON Response: Uses jq to extract specific fields from the JSON response and format them as CSV.
6- Clean Up: Deletes the JSON response file after processing.


# Configuration
Set Jira Credentials and Endpoint

- Replace the placeholder values with your actual Jira credentials and URL:

    batch
    Copy code
    set "JIRA_USER=your_jira_email"
    set "JIRA_API_TOKEN=your_jira_api_token"
    set "JIRA_URL=your_jira_query_url"
    Set Output File


- Specify the path and name of the output CSV file:

      batch
      Copy code
      set "OUTPUT_FILE=jira_all.csv"
      Detailed Steps
      Set Local Environment

- The script begins by setting the local environment:
      
      batch
      Copy code
      @echo off
      setlocal
      Set Jira Credentials and Endpoint

- The script sets the Jira user, API token, and URL:
        
        batch
        Copy code
        set "JIRA_USER=your_jira_email"
        set "JIRA_API_TOKEN=your_jira_api_token"
        set "JIRA_URL=your_jira_query_url"
        Set Output File

- The script specifies the output file for the CSV data:
      
      batch
      Copy code
      set "OUTPUT_FILE=jira_all.csv"
      Make API Request

- The script makes an API request to Jira and saves the response to response.json:
      
      batch
      Copy code
      curl -u %JIRA_USER%:%JIRA_API_TOKEN% -X GET -H "Content-Type: application/json" %JIRA_URL% -o response.json
      Check for Errors

- The script uses jq to check if the response contains any errors:

      batch
      Copy code
      "C:\Program Files\jq\jq.exe" -e .errors response.json >nul 2>&1
      if %ERRORLEVEL% equ 0 (
          echo Error in response
          type response.json
          exit /b 1
      )

- Process JSON Response
- The script uses jq to process the JSON response and extract specific fields, saving them as CSV:
      
      batch
      Copy code
      "C:\Program Files\jq\jq.exe" -r ".issues[] | [.key, .fields.summary, .fields.assignee.displayName, .fields.status.name,  (.fields.customfield_10020[0] | .name ), .fields.created, .fields.updated] | @csv" response.json > %OUTPUT_FILE%
      Clean Up

- The script deletes the response.json file:
      
      batch
      Copy code
      del response.json
      End Local Environment
      
- The script ends the local environment and pauses:
      
      batch
      Copy code
      endlocal
      pause


- Running the Script:
1- Ensure that curl and jq are installed and correctly configured.
2- Open a command prompt and navigate to the directory where the script is located.
3- Run the script by typing its name and pressing Enter.
4- The script will execute the steps described above and save the extracted data to the specified CSV file.


























