# Jira
- Jira is a popular project management tool used by software development teams to plan, track, and release software.
## Jira Authentication with Jenkins
- Get your API Tokin `JIRA_API_TOKEN` from Jira website
- Go to `Credentials` in jenkins and add specific one for Jira Credentials
- Download `Jira Plugin`

Step 1: Getting API token for Jira
Navigate to Security Settings:

Once logged in, click on the Security tab in the left sidebar.
Find API Tokens Section:

Scroll down to the API Tokens section.

Click on Create API Token:

Click the Create API Token button.
Set Up Token Details:

A dialog box will appear.
Enter a label for your API token (e.g., Jenkins Integration).
Create the Token:

Click Create.


Step 2: Install the Jira Plugin in Jenkins

Step 3: Integrating Jira in Jenkins
Open Jenkins Dashboard:

Navigate to Manage Jenkins:

Click on Manage Jenkins in the sidebar.
Configure System:

Click on Configure System.
Jira Servers:

Scroll down to the Jira Servers section.
Click Add Jira Server.
Add Jira Details:

Enter the Name for your Jira server.
Enter the Jira URL (e.g., https://yourcompany.atlassian.net).
Enter your Username and API token.
Click Test Connection to verify the connection.


Step 5: Manage your Jira

Add your epics, your tasks, and your child tasks 

Add all the team members

Divide the project into different phases
Create the Sprints accordingly and set the deadlines and the due dates.

(Optional) Assign each team member to a role and to a different task

Step 6: Configure Jenkins Job to Integrate with Jira
Create or Configure a Jenkins Job:

Go to your Jenkins instance and create a new job or configure an existing one.
Configure Jira Integration:

In the job configuration, scroll down to the Post-build Actions section.
Click Add post-build action.
Select Jira Issue Updater.
Configure the Jira integration settings, such as updating issues based on build results.
Click Save.


Step 7: Test the Integration
Create a Jira Issue:

Create a new issue in your Jira project.
Trigger a Jenkins Build:

Manually trigger a build in Jenkins or wait for an automatic trigger.
Check Jira for Updates:

Verify that the Jira issue is updated based on the Jenkins build status.
