<!-- > Please note that this was developed as part of a project during our Brightskies © Embedded Software Internship. -->
# CI-CD-Jenkins

<div>
  <img src="Knowledge/Docker/Brightskies_ci_jenkins%20Image/asserts/p.png" alt="project details" width="600">
</div>

### Table of Contents
  - **[Jenkins](Jenkins/):** Jenkins configurations and scripts
  - **[Docker Image](Docker%20Image/):** Docker images used in the project
  - **[Static Code Analysis](Static%20Code%20Analysis/):** Static code analysis tools and results
  - **[Knowledge](Knowledge/):** Documentation and knowledge base
    - **[Architecture](Knowledge/Architecture/):** Architectural designs and diagrams
      - **[Test Cases with Pipeline Code](Knowledge/Architecture/Test%20cases%20with%20pipeline%20code/):** Test cases related to the pipeline
    - **[Docker](Knowledge/Docker/):** Docker-related information and examples
      - **[Allure](Knowledge/Docker/Allure/):** Allure reporting for tests
      - **[Asserts](Knowledge/Docker/asserts/):** Assertions for tests
      - **[Brightskies_CI_Jenkins Image](Knowledge/Docker/Brightskies_ci_jenkins%20Image/):** CI Jenkins image configurations
      - **[Docker Swarm](Knowledge/Docker/Docker%20Swarm/):** Docker Swarm configurations and examples
      - **[Jenkins_Ubuntu](Knowledge/Docker/Jenkins_Ubuntu/):** Jenkins configurations for Ubuntu
      - **[Simple Docker Commands](Knowledge/Docker/Simple%20Docker%20commands/):** Basic Docker command examples
    - **[Git Extension](Knowledge/Git_Extension/):** Git extensions and usage
    - **[Integration Testing](Knowledge/IntegrationTesting/):** Integration testing strategies
      - **[PyTest](Knowledge/IntegrationTesting/PyTest/):** PyTest configuration and examples
        - **[Integration & Unit Testing & Reporting](Knowledge/IntegrationTesting/PyTest/Integration&UnitTesting&Reporting/):** Details on integration and unit testing with reporting
    - **[Jenkins](Knowledge/Jenkins/):** Additional Jenkins documentation
      - **[Errors & Solutions](Knowledge/Jenkins/Errors&Sol/):** Common errors and their solutions
      - **[Integrate GTest](Knowledge/Jenkins/Integrate_Gtest/):** Integration of GTest in Jenkins
      - **[Jenkins Email Notification](Knowledge/Jenkins/Jenkins_Email_Notification/):** Email notification setup in Jenkins
    - **[Jenkins Agent](Knowledge/Jenkins_Agent/):** Configuration and setup of Jenkins agents
    - **[Jira Integration](Knowledge/Jira_Integration/):** Integration of Jira with the project
      - **[Import CSV](Knowledge/Jira_Integration/import_csv/):** CSV import configurations
    - **[ngrok](Knowledge/ngrok/):** Setup and usage of ngrok
    - **[Prerequisites](Knowledge/Prerequisites/):** Required tools and software
    - **[Pytest](Knowledge/Pytest/):** Configuration and usage of Pytest
    - **[Reporting](Knowledge/Reporting/):** Reporting tools and setups
      - **[Allure](Knowledge/Reporting/Allure/):** Allure setup and usage
    - **[Unit Testing](Knowledge/UnitTesting/):** Unit testing strategies and examples
      - **[Code Coverage](Knowledge/UnitTesting/Code%20Coverage/):** Code coverage configurations and tools
      - **[GTest](Knowledge/UnitTesting/Gtest/):** GTest configurations and usage
      - **[Static Code Analysis](Knowledge/UnitTesting/Static%20Code%20Analysis/):** Static code analysis configurations


------

# Project Setup Guide 🛸

This guide will walk you through setting up the project locally using Docker and Jenkins. The setup includes volume mapping to ensure data persistence and cloning the repository into the Jenkins home directory. Additionally, we'll cover how to install necessary plugins and tools in Jenkins.

---

## Prerequisites

1. **Docker Desktop**:
   - Download and install Docker Desktop from [https://www.docker.com/](https://www.docker.com/).
   - After installation, sign in to Docker Desktop and ensure it is running.

2. **Git** installed on your system.

---


## Step 1: Clone the Repository

First, clone the repository to your local machine:

```bash
git clone https://github.com/AhmedSamymoh/CI-CD-Jenkins.git
cd CI-CD-Jenkins
```


## Step 2: Build the Docker Image 🐋

To build the Jenkins Docker image, run the following command:


```bat
cd '.\Docker Image\'
```

```bash
docker build -t brightskies_ci_jenkins:latest .
```

## Step 3: Start Jenkins with Docker Compose
Start the Jenkins container using Docker Compose:

```bash
mkdir C:/Jenkin_Workspace
```
```bash
docker-compose up
```

- the docker compose will:
  - Start the Jenkins container.
  - Mount the host directory `C:/Jenkin_Workspace` to `/jenkins_home` in the container for persistent storage.
  - Map port `8082` on your host to port `8080` in the container (Jenkins UI).
  - Map port `50000` for Jenkins agent communication.

## Step 4: Docker Volume Mapping
-The `docker-compose.yml` file defines the following volume mapping:

```yml
Copy
version: '3.8'

services:
  jenkins:
    image: brightskies_ci_jenkins
    ports:
      - "8082:8080"
      - "50000:50000"
    volumes:
      - C:/Jenkin_Workspace:/jenkins_home
```

### Explanation:
- Volume Mapping: The C:/Jenkin_Workspace directory on your host is mapped to /jenkins_home in the container. This ensures that all Jenkins data (jobs, configurations, plugins, etc.) is stored persistently on your host machine.

### Benefits:
- Data Persistence: Jenkins data will persist even if the container is stopped or restarted.
- Easy Access: You can directly access Jenkins data from your host machine.


## Step 5: Access Jenkins and Install Plugins

- Access Jenkins:
  - Open your browser and navigate to:
  
    ```
    http://localhost:8082
    ```
  
  - Unlock Jenkins using the initial admin password.  
  - You can find this `password` in the Jenkins logs or at:
  
    ```
    C:/Jenkin_Workspace/secrets/initialAdminPassword
    ```

- Add Jenkins Credentials:
  - Navigate to **Manage Jenkins** → **Manage Credentials**.
  - Under **Stores scoped to Jenkins**, click on **Global credentials**.
  - Click **Add Credentials** and enter:
    - **Kind**: Username with password
    - **Scope**: Global (Recommended)
    - **Username**: `<your-username>`
    - **Password**: `<your-password>`
    - **ID**: `git-credentials`
    - **Description**: `Git authentication for Jenkins`
  - Save the credentials.

### Install Plugins:

After unlocking Jenkins, you will be prompted to install plugins. Install the following recommended plugins:

- **Git Plugin** – Integrates Jenkins with Git repositories.
- **GitLab Plugin** – Required if using GitLab for version control and CI/CD.
- **Allure Jenkins Plugin** – Generates Allure Test Reports for test automation.
- **GitHub Pull Request Builder Plugin** – Triggers builds for pull requests from GitHub.



### Installation:
After unlocking Jenkins, navigate to:
- **Manage Jenkins** → **Plugins Manager** → **Available Plugins**
- Search for the plugins and install them.


- Configure Tools:

  - Go to Manage Jenkins > Global Tool Configuration.

  - Configure tools like Git, Docker, and any other dependencies required for your project.

----

## Step 6: Cloning the Repository in Jenkins Home

Clone the repository into `C:/Jenkin_Workspace` (host) or `/var/jenkins_home` (container):

```bat
# Inside Jenkins Container
docker ps  # Get container ID or name
docker exec -it <container_id_or_name> bash
```

```bash
cd /var/jenkins_home
git clone https://github.com/AhmedSamymoh/CI-CD-Jenkins.git
```

```sh
cd /var/jenkins_home/CI-CD-Jenkins
ls
```
- Expected output:
```
root@bf366f7f9989:/var/jenkins_home/CI-CD-Jenkins# ls
'Docker Image'   Jenkins   Jira   Knowledge   LICENSE   Ngrok   README.md   Static_Code_Analysis
```


## Step 7: Configuration of Jira and Ngrok scripts
   
### Jira Sprint Issues Extractor
- Edit jira.sh , Visit [`Jira README.md`](./Jira/README.md) ⚙️

```bash
JIRA_USER="your_email"  
JIRA_API_TOKEN="your_token"  
JIRA_URL="your_jira_url"  
```
   
### CppCheck MisraC Static Analysis
- Making `Misra_src_check.sh` executable
``` bash
cd /var/jenkins_home/CI-CD-Jenkins/Static_Code_Analysis
chmod 777 Misra_src_check.sh
```

### Ngrok & GitHub Webhooks  
- **Update `webhook.py`** , Visit [`Ngrok README.md`](./Ngrok/README.md) ⚙️

```
cd /var/jenkins_home/CI-CD-Jenkins/Ngrok
vim webhook.py
```

```python
REPO_OWNER = "YourUserName"  
REPO_NAME = "Repo"  
GITHUB_TOKEN = "*******Token*******"  
```

## Step 8: Verify Jenkins Setup

- Once Jenkins is up and running, verify the setup by:

- Creating a new Jenkins job or pipeline.

- Configuring the job to use the cloned repository.

- Running a build to ensure everything is working correctly.

- Using Jenkins Pipelines, create a Jenkinsfile in your repository. Here’s an example:

```groovy
pipeline {
    agent any
    stages {
        stage('Build') {
            steps {
                echo 'Building the project...'
            }
        }
        stage('UnitTesting') {
            steps {
                echo 'Running tests...'
            }
        }
        stage('Sprint Release Notes') {
            steps {
                echo 'Sprint Release Notes...'
            }
        }
    }
}
```


This pipeline defines three stages: Build, Test, and Deploy. Customize it according to your project requirements.


## Step 8: Configure Jenkins Credentials

To securely interact with private repositories, Docker Hub, or other services, configure credentials in Jenkins.

### Adding GitHub Credentials:
1. Go to **Manage Jenkins** → **Manage Credentials**.
2. Select **(global)** under **Stores scoped to Jenkins**.
3. Click **Add Credentials** → Select **Username with password** or **SSH Key**.
4. Enter your GitHub username and personal access token.
5. Save the credentials.

### Adding Docker Hub Credentials:
1. Navigate to **Manage Jenkins** → **Manage Credentials**.
2. Click **Add Credentials** → Select **Username with password**.
3. Enter your Docker Hub username and password.
4. Save the credentials.


## Step 9:


----
