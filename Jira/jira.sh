#!/bin/bash

# ######## Set your Jira credentials and endpoint ######## 
JIRA_USER="add your email here"
JIRA_API_TOKEN="add your token here"
JIRA_URL="ADD YOUR JIRA URL HERE"

# ######## Output file ######## 
OUTPUT_FILE="jira_all_issues.csv"

# ######## Make API request and save the response to a file ######## 
curl -u "$JIRA_USER:$JIRA_API_TOKEN" -X GET -H "Content-Type: application/json" "$JIRA_URL" -o response.json

# Check if the response contains an error
if jq -e .errors response.json > /dev/null 2>&1; then
    echo "Error in response"
    cat response.json
    exit 1
fi

# Process the JSON response to extract the data and save it as CSV
{
    echo "KEY,SPRINT,SUMMARY,ASSIGNEE,STATUS,START DATE,UPDATED"
    jq -r '.issues[] | [.key, (.fields.customfield_10020[0].name // "N/A"), .fields.summary, (.fields.assignee.displayName // "Unassigned"), .fields.status.name, .fields.created, .fields.updated] | @csv' response.json
} > "$OUTPUT_FILE"

# ######## Clean up ######## 
rm response.json

echo "CSV file has been saved to $OUTPUT_FILE"

# ######## Run the Python script ######## 
echo "Running HighestSprint.py!"
python3 HighestSprint.py
