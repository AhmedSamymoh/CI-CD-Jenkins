# Jira Sprint Issues Extractor

This project consists of scripts to extract the highest sprint issues from Jira and generate a formatted text file.

## Requirements
- Python 3.x
- `jq` (for bash script)
- Jira API access with appropriate credentials
- Jenkins (for CI/CD integration)

## Files
1. `HighestSprint.py` - Python script to process Jira issues CSV and extract highest sprint
2. `jira.sh` - Bash script to fetch issues from Jira API and process them

## Configuration
Before running the scripts, you need to configure:

### In `jira.sh`:
```bash
JIRA_USER="add your email here"
JIRA_API_TOKEN="add your token here"
JIRA_URL="ADD YOUR JIRA URL HERE"
```
### In HighestSprint.py (optional):

```python
INPUT_FILE = 'jira_all_issues.csv'  # Change if needed
OUTPUT_FILE = 'jira_sprint_issues.txt'  # Change if needed
```

## Usage

1. Make the bash script executable:
```bash
chmod +x jira.sh
```

2. Run the bash script:

```bash
./jira.sh
```

### This will:

- Fetch issues from Jira API

- Save them to a CSV file (jira_all_issues.csv)

- Run the Python script to process the CSV

- Generate a text file (jira_sprint_issues.txt) with the highest sprint issues

---

## Jenkins Integration
Here's the Jenkins pipeline stage for integrating this tool:

``` groovy
stage('Release Notes') {
    parallel {
        stage('Jira Release Notes') {
            when {
                expression { env.ghprbSourceBranch == 'master' && env.ghprbPullId }
            }
            steps {
                script {
                    echo "This is a pull request from branch: ${env.ghprbSourceBranch}"
                    currentBuild.displayName = "Release Notes v.${env.ghprbPullId} - Build #${env.BUILD_NUMBER}"
                }
                echo "Generating Jira release notes..."
                dir('/Tools/Jira') {
                    sh 'apt-get install jq -y'
                    sh 'chmod +x ./jira.sh'
                    sh './jira.sh'
                    echo "Jira Release Notes:"
                    sh 'cat jira_sprint_issues.txt'
                }
            }
        }
    }
}
```

## Output Format
The output file (jira_sprint_issues.txt) will contain:

```txt
[Sprint X]

[KEY-123] : Issue description

[KEY-456] : Another issue description
```