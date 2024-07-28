# Branch Checkout and Build
This Jenkins pipeline script is designed to checkout a specific branch from a Git repository and execute build steps on it in a Windows environment.

# Pipeline Overview
This Jenkins pipeline script consists of two main stages: checking out a specified branch from a Git repository and running a build script (test2.bat). The branch to checkout can be specified as a parameter.

# Pipeline Parameters
BRANCH_NAME: Specifies the branch to checkout and build. The default value is test.
# Pipeline Stages
- Checkout Stage
The Checkout stage fetches all branches from the remote repository and checks out the specified branch.

      stage('Checkout') {
      steps {
        script {
            bat """
            git fetch --all
            git checkout ${params.BRANCH_NAME}
            """
        }
      }



  
- Build Stage
The Build stage echoes the branch being built and executes the test2.bat file.

          stage('Build') {
      steps {
        echo "Building branch: ${params.BRANCH_NAME}"
        echo "test test "
        bat """
        test2.bat 
        """
        }
          }




# Usage
Trigger the Pipeline: When triggering the pipeline, specify the BRANCH_NAME parameter to checkout and build a different branch. By default, the pipeline will checkout and build the test branch.

