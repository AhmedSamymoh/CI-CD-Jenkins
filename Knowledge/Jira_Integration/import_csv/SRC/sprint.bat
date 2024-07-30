@echo off
setlocal

REM Set your Jira credentials and endpoint
set "JIRA_USER=ranamohamed2722003@gmail.com"
set "JIRA_API_TOKEN=ATATT3xFfGF0_vSjuzRXb76JcaFwbD8ReV00bNWBZLxc9sCh8w9x_g8SZSo2q2FB9QpgpdH9tArg38310C7FMN2vM_89hJGH9gi2vfRsA67RCyk9xR9JAyH0OOFG0UF7j_PL-tQ_cE9588NHZ88LY6HoaGxQDyCxgR-I00_xbCaEAWOhH7LRNSw=F7021664"
set "JIRA_URL=https://ahmedselnozahy.atlassian.net/rest/api/2/search?jql=project=CCB"

REM Output file
set "OUTPUT_FILE=jira_sprint_issues.txt"

REM Make API request and save the response to a file
curl -u %JIRA_USER%:%JIRA_API_TOKEN% -X GET -H "Content-Type: application/json" %JIRA_URL% -o response.json

REM Check if the response contains an error
"C:\Program Files\jq\jq.exe" -e .errors response.json >nul 2>&1
if %ERRORLEVEL% equ 0 (
    echo Error in response
    type response.json
    exit /b 1
)

REM Process the JSON response to extract issues with sprint ID = 1 and save them as text
"C:\Program Files\jq\jq.exe" -r ".issues[] | select((.fields.customfield_10020[]? | .id == 1)) | [.key, .fields.summary, .fields.assignee.displayName, .fields.status.name, (.fields.customfield_10020[] | select(.id == 1) | .id // \"No Sprint\"), .fields.created, .fields.updated] | @csv" response.json > %OUTPUT_FILE%

REM Clean up
del response.json

echo Filtered issues have been saved to %OUTPUT_FILE%

endlocal
pause
