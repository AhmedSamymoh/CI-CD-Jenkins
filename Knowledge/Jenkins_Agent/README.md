# 📌 Setup-SSH-For-Containers-Jenkins 📌
 ##  🚩 Abstract and Architecture:
 We have two containers, one is Jenkins and the other is a slave has applications & tools. We want to connect the slave to the Jenkins container. So Jenkins can run and excute commands on the other container. We will use SSH to connect the two containers based on the Docker-compose Network.

 ![schema](https://github.com/user-attachments/assets/6386458d-e333-4057-a0df-f87f8a8fee3c)




## ⚙️ Prerequisites:
- Jenkins Image with SSH-Client installed.
- Tools Image with the tools required & SSH-Server installed.
- Docker-compose installed.


## 👨‍💻 Imagine the scene :
- We are going to Use Jenkins as an interface for the other containers to run pipelines using the other containers which contain tools and applications.
- After configuring the SSH connection between the Jenkins container and the other containers, we can run pipelines on the other containers using Jenkins.
- This approach provide us with varity of containers as we can add more containers to the Jenkins container to run different pipelines. (In this example we have only one container )

![alt text](assets/10006758525.jpg)




## Steps:
1. ╰┈➤ Create a Dockerfile for Jenkins container:
```Dockerfile
# You will find the files in this repo
FROM jenkins/jenkins:lts

# Set environment variables
ENV JENKINS_HOME /var/jenkins_home

# Switch to the root user to install additional packages
USER root

# Update the package list and install additional tools
RUN apt-get update && apt-get install -y \
    nano \
    openssh-client \
    vim \
    curl \
    && rm -rf /var/lib/apt/lists/*



# Expose Jenkins web and agent ports
EXPOSE 8080 50000
```
2. ╰┈➤ Create a Dockerfile for the tools container:
```Dockerfile
FROM ubuntu:latest
#Updating the package list
RUN apt-get update

#Installing the essential Tools
RUN apt-get install -y \
    software-properties-common \
    nano \
    openssh-server \
    wget \
    unzip \
    git \
    gnupg2 \
    && rm -rf /var/lib/apt/lists/*

#Installing Python3 and pip
RUN apt-get update && apt-get install -y python3
RUN apt-get update && apt-get install -y python3-pip

#installing Pytest 
RUN apt update && apt install -y python3-pytest


# Install MinGW64
RUN apt-get update && apt-get install -y \
    mingw-w64 \
    && rm -rf /var/lib/apt/lists/*

#install CppCheck
RUN apt-get update && apt-get install -y \
    cppcheck \
    && rm -rf /var/lib/apt/lists/*


# Install CMake
RUN apt-get update && apt-get install -y \
    cmake \
    && rm -rf /var/lib/apt/lists/*


# Install Google Test
RUN apt-get update && apt-get install -y \
    libgtest-dev \
    && rm -rf /var/lib/apt/lists/*


# Install JDK-17
RUN apt-get update && apt-get install -y \
    openjdk-17-jdk \
    && rm -rf /var/lib/apt/lists/*


# Install Allure 2.30
RUN wget https://github.com/allure-framework/allure2/releases/download/2.30.0/allure-2.30.0.zip && \
    unzip allure-2.30.0.zip -d /opt && \
    ln -s /opt/allure-2.30.0/bin/allure /usr/bin/allure && \
    rm allure-2.30.0.zip


# Set environment variables
ENV JAVA_HOME=/usr/lib/jvm/java-17-openjdk-amd64
ENV PATH=$PATH:/opt/w64devkit/bin:/usr/lib/gcc/x86_64-w64-mingw32

# Expose SSH port
EXPOSE 22


# Default command
CMD ["tail", "-f", "/dev/null"]
```




3. ╰┈➤ Build the Jenkins image:
```bash
#Make sure to go to the directory where the Dockerfile is located before running the command
docker build -t jenkinsssh:2 .
```

4. ╰┈➤ Build the tools image:
```bash
#Make sure to go to the directory where the Dockerfile is located before running the command
docker build -t tools:1.2 .
```

5. ╰┈➤ If you use the following command, you will see the images you have created:
    -  ```bash
       docker images
       ```


6. ╰┈➤ Then create a Docker-compose file:
```yaml
version: '3.8'

services:
  jenkins: # Jenkins container
    image: jenkinsssh:2
    container_name: jenkinsssh
    ports:
      - "8085:8080"
    volumes: # Mount the volume to the container
      - jenkins_home:/var/jenkins_home
    networks: # Connect the container to the network
      - jenkins_network

  tools: # Tools container
    image: tools:1.2
    container_name: tools
    networks:
      - jenkins_network
    volumes: # Mount the volume to the container
      - jenkins_home:/var/jenkins_home

volumes:
  jenkins_home:

networks: # Create a network
  jenkins_network: # Connect all the containers to the network
    driver: bridge
```

7. ╰┈➤ Run the Docker-compose file:
```bash
docker-compose up -d
```

8. ╰┈➤ Check the containers You will see the two containers running:
```bash
docker ps
```

9. ╰┈➤ Now we are going to Test the SSH connection between the Jenkins container and the tools container:
    - Go to the Tools container:
    ```bash
    docker exec -it "container name (or ID)" bash
    ```
    - go to the ssh directory to change the sshd_config file to allow the root user to connect:
    ```bash
    nano /etc/ssh/sshd_config
    ```
    - Scroll down to the PermitRootLogin uncomment it if conmmented and change it to yes:
    
    - Now check the status of the ssh-server:
    ```bash
    service --status-all
    ```
    - Almost you will find it stopped like this: [-], so start it:
    ```bash
    service ssh start
    ```
    - We need to know the root password to connect to the container from Jenkins, so change the root password:
    ```bash
    passwd root
    ```
    - Now exit the container:
    ```bash
    exit
    ```
    - Now we need to know the IP address of the tools container to connect to it from Jenkins:
    ```bash
    docker inspect tools | grep "IPAddress"
    # Don't forget to change `tools` to the name of your container
    ```
    - Now we are going to connect to the tools container from Jenkins:
    - Go to the Jenkins container:
    ```bash
    docker exec -it jenkinsssh bash
    # Don't forget to change `jenkinsssh` to the name of your container
    ```
    - Now we are going to connect to the tools container:
    ```bash
    ssh root@tools_IP
    ```
    - You will be asked to enter the password, enter the password you have set before.
    - If you have connected successfully, you will see the tools container name in the terminal.
    - Now exit the tools container:
    ```bash
    exit
    ```
    - Now exit the Jenkins container:
    ```bash
    exit
    ```
    - Now we have successfully 🎉 connected the Jenkins container to the tools container using SSH .






  # Using Agents in Jenkins:
  ***Now we will apply the same approach to Jenkins Agents , cuz it makes the process easer***
1. After creating the both container we will make the tools container as an agent for Jenkins Because using the Agents make the process easer to manage and control the containers.
2. Go to Jenkins and **Manage Jenkins**

3. Click on **Manage Nodes and Clouds**

4. Click on **New Node**

5. Fill the form as the following:
    - **Node Name**: Tools-node
    - **Remote** root directory: /var/jenkins_home
    - **Labels**: Tools-node
    - **Launch method**: Launch agent by connecting it to the master
    - **Host**: Tools
    - **Availability**: Keep this agent online as much as possible
    - **Click Save**
    - Now you will see the Tools-node in the Nodes list it will be offline.
    - You will find the commands to run on you machine for our case pick the first one which is linux
        - ```bash
          curl -sO http://localhost:8081/jnlpJars/agent.jar
          java -jar agent.jar -url http://localhost:8081/ -secret 521840ae4207ed1aa0d59ffcf18cec17e6fda112539fad0fc86e72f39eeb02f5 -name Tools-node -workDir "/var/jenkins_home"
          ```
    - ⚠️ **Note**: Don't copy and paste the code directly because we are dealing with containers not on the cloud mahcines , so we will donwload the file manulally and transfer it to the docke container.
    - On you machine it self **Not the containers** run the following command to download the agent.jar file:
      ```bash
      curl -sO http://localhost:8081/jnlpJars/agent.jar
      ```


    - Now we are going to download the agent.jar file:
      ```bash
      wget http://localhost:8085/jnlpJars/agent.jar
      ```

    - Run the following command to start the agent:
      ```bash
      java -jar agent.jar -url http://localhost:8081/ -secret 521840ae4207ed1aa0d59ffcf18cec17e6fda112539fad0fc86e72f39eeb02f5 -name ggggggg -workDir "/asdsa/asdasd"
      ```

    - Now you will see the Tools-node in the Nodes list it will be online on Jenkins.














[Good tutorial](https://www.youtube.com/watch?v=9RsmPNs7gT0)
