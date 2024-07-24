
# ONLY RUN the changed file (the last commited file in github project)


- This Jenkins pipeline script is designed to check for changes in specific batch files (test1.bat, test2.bat, test3.bat) and run them in parallel if they have been modified. The pipeline consists of three main stages: Checkout, Check for Changes, and Run Parallel Jobs.



# Check for Changes Stage

      stage('Check for Changes') {
    steps {
        script {
            // Run git command to get changed files
            def changes = bat(script: '\"C:\\Program Files\\Git\\bin\\git.exe\" diff --name-only HEAD~1 HEAD', returnStdout: true).trim()
            
            // Check if the specific batch files are in the list of changed files
            env.RUN_TEST1 = changes.contains('test1.bat') ? 'true' : 'false'
            env.RUN_TEST2 = changes.contains('test2.bat') ? 'true' : 'false'
            env.RUN_TEST3 = changes.contains('test3.bat') ? 'true' : 'false'
        }
    }

  - Purpose: This stage runs a Git command to determine which files have changed between the last commit and the current commit.

  - 
# Key Steps:
- Git Diff Command: Executes git diff --name-only HEAD~1 HEAD to get a list of changed files.


- Set Environment Variables: Checks if test1.bat, test2.bat, or test3.bat are in the list of changed files and sets corresponding environment variables (RUN_TEST1, RUN_TEST2, RUN_TEST3) to true or false.

![image](https://github.com/user-attachments/assets/86caf548-ccf2-40b0-b745-51bfed2dff2e)




![image](https://github.com/user-attachments/assets/ef62c8f2-8f4f-414f-b0d8-88bb77016960)




![image](https://github.com/user-attachments/assets/b6e3fc9b-d190-4698-bf58-bc42b16639ed)




![image](https://github.com/user-attachments/assets/6610a4b9-4f2a-46f2-ab04-c9e9c7ecd3db)



![image](https://github.com/user-attachments/assets/9ff5e3c4-6ba4-43f2-a690-57e0e9e21bf5)




