# Docker and Jenkins Setup Guide

This guide walks you through the process of setting up two Docker containers using Dockerfiles, linking them with Docker Compose, and configuring Jenkins in a Docker swarm environment.

## Prerequisites

- **Docker Desktop** or **Docker Daemon** installed

## Steps

### 1. Create Dockerfile 1

Create the first Dockerfile with the required format and specifications. (Example given in the same folder)

### 2. Create Dockerfile 2

Create the second Dockerfile with the required format and specifications. (Example given in the same folder)

### 3. Create Docker Compose File

Create a Docker Compose file that links Dockerfile 1 and Dockerfile 2. Ensure that the services are properly defined and can communicate with each other. (Example given in the same folder)

### 4. Open Terminal and Docker Desktop

- Open your computer terminal.
- Open **Docker Desktop**. If you do not have Docker Desktop, start the Docker Daemon using the command:
  ```bash
  dockerd

### 5. Change Directory to Dockerfile 1
Navigate to the directory where Dockerfile 1 is located:
    cd /path/to/Dockerfile1

### 6. Create the Image for Dockerfile 1
Build the Docker image for Dockerfile 1 using the command:
    docker build .

### 7. Change Directory to Dockerfile 2
Navigate to the directory where Dockerfile 2 is located:
   cd /path/to/Dockerfile2

### 8. Create the Image for Dockerfile 2
Build the Docker image for Dockerfile 2 using the command:
    docker build .

### 9. Go to the Directory of the Docker Compose File
Navigate to the directory where the Docker Compose file is located:
    cd /path/to/docker-compose-file

### 10. Run Docker Compose
Run the Docker Compose file to start the services:
    docker-compose -f <filename.yml> up

### 11. Verify Containers are Running
Ensure that both containers are up and running using the command:
    docker ps

### 12. Set Up Jenkins
Try to access it using the chosen local host IP, if it does not run, use the following command inside the container 
    java -jar /usr/share/java/jenkins.war

The command to enter the container as a host is:
    docker exec -u 0 -it container-name bash

### 13. Install Jenkins Plugins
Finish installing the required plugins for Jenkins.

### 14. Start Docker Daemon in Container
Run the Docker Daemon within the container:
    dockerd

### 15. Initialize Docker Swarm
Initialize Docker Swarm in the container, making it the managing node:
    docker swarm init
this container will then become the managing node for the swarm, copy the given token in order to join the swarm in the other container.

### 16. Run the other container and repeat the same steps, but join the swarm as worker. 
