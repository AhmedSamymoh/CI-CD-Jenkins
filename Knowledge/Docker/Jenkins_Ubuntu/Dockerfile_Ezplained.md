# Development Environment Docker Setup
- This Dockerfile sets up a comprehensive development environment using the latest versions of essential tools like JDK, Ubuntu, Jenkins, Google Test, Pytest, MinGW64, CppCheck, and Allure. Follow the steps below to build and run the Docker container.

## Prerequisites
- Docker Desktop installed on your machine.


## Dockerfile Explanation
- Base Image  :  dockerfile
- 
## Use the latest Ubuntu base image
    FROM ubuntu:latest
    
## This line specifies that the base image for the Docker container is the latest version of Ubuntu.

## Set the environment variable to avoid prompts during package installation
    
    ENV DEBIAN_FRONTEND=noninteractive
    The DEBIAN_FRONTEND environment variable is set to noninteractive to prevent any prompts during the package installation process, making it suitable for automated builds.


## Update the package list and install necessary packages

    RUN apt-get update && \
        apt-get install -y \
        openjdk-21-jdk \
        wget \
        software-properties-common \
        git \
        python3 \
        python3-pip \
        python3-venv \
        curl \
        vim \
        gnupg2 \
        apt-transport-https \
        build-essential \
        cmake \
        unzip \
        && apt-get clean
- This command updates the package list and installs essential packages:

        openjdk-21-jdk: Java Development Kit.
        wget: Utility for downloading files.
        software-properties-common: Utilities for managing software repositories.
        git: Version control system.
        python3: Python 3 interpreter.
        python3-pip: Python package installer.
        python3-venv: Python virtual environment.
        curl: Tool for transferring data with URLs.
        vim: Text editor.
        gnupg2: GNU Privacy Guard for encryption.
        apt-transport-https: Transport method for APT.
        build-essential: Essential packages for building software.
        cmake: Tool for managing the build process.
        unzip: Utility for unzipping files.
        The apt-get clean command removes cached package files to reduce image size.

## Install Jenkins

        RUN curl -fsSL https://pkg.jenkins.io/debian/jenkins.io.key | apt-key add - && \
            sh -c 'echo deb http://pkg.jenkins.io/debian-stable binary/ > /etc/apt/sources.list.d/jenkins.list' && \
            apt-get update && \
            apt-get install -y jenkins && \
            apt-get clean

            
- This sequence installs Jenkins:

1-  Adds the Jenkins Debian repository key.
2-  adds the Jenkins repository to the sources list.
3-  Updates the package list.




# Install Google Test
        RUN git clone https://github.com/google/googletest.git /usr/src/gtest && \
            cd /usr/src/gtest && \
            git checkout $(git describe --tags) && \
            cmake . && \
            make && \
            make install && \
            cd && \
            rm -rf /usr/src/gtest
 
 - This sequence installs Google Test:

1- Clones the Google Test repository.
2- Checks out the latest tag.
3- Configures the build with CMake.
4- Compiles and installs Google Test.
5- Cleans up the source directory.
6- Create and Activate Virtual Environment, then Install Pytest

## Install Pytest
    
    RUN python3 -m venv /opt/venv && \
        /opt/venv/bin/pip install --upgrade pip && \
        /opt/venv/bin/pip install --upgrade pytest

- This command:

1- Creates a Python virtual environment in /opt/venv.
2- Upgrades pip within the virtual environment.
3- Installs the latest version of pytest in the virtual environment.


## Install MinGW64
    RUN apt-get update && apt-get install -y \
        mingw-w64 \
        && rm -rf /var/lib/apt/lists/*
    This installs MinGW64, a toolchain for compiling Windows applications on Unix-like systems.


## Install CppCheck
    RUN apt-get update && apt-get install -y \
        cppcheck \
        && rm -rf /var/lib/apt/lists/*
    This installs CppCheck, a static analysis tool for C/C++ code.

## Install Allure 2.30

    RUN wget https://github.com/allure-framework/allure2/releases/download/2.30.0/allure-2.30.0.zip && \
        unzip allure-2.30.0.zip -d /opt && \
        ln -s /opt/allure-2.30.0/bin/allure /usr/bin/allure && \
        rm allure-2.30.0.zip

- This sequence installs Allure:

1- Downloads the Allure binary zip file.
2- Unzips it into the /opt directory.
3- Creates a symbolic link to the Allure executable in /usr/bin.
4- Removes the downloaded zip file.
5- Set PATH Environment Variable

## Make the virtual environment available in the PATH
        ENV PATH="/opt/venv/bin:$PATH"
        This updates the PATH environment variable to include the Python virtual environment's bin directory.

## Expose the Jenkins port
    EXPOSE 8085
    This exposes port 8085 for Jenkins.

## Set Jenkins home
    ENV JENKINS_HOME=/var/lib/jenkins
    This sets the JENKINS_HOME environment variable to /var/lib/jenkins.


## Override the default Jenkins port
    RUN sed -i 's/HTTP_PORT=8080/HTTP_PORT=8085/' /etc/default/jenkins
    This modifies the Jenkins configuration to use port 8085 instead of the default 8080.

## Start Jenkins using the service command and keep the container running
    CMD ["sh", "-c", "service jenkins start && tail -f /var/log/jenkins/jenkins.log"]

- This command:
1- Starts the Jenkins service.
2- Keeps the container running by tailing the Jenkins log file.
3- Building and Running the Container
4- Build the Docker Image


docker build -t image .

This command builds the Docker image and tags it as dev-environment.


Run the Docker Container

    docker run -d -p 8085:8085 --name dev-container dev-environment
    This command runs the Docker container in detached mode, mapping port 8085 of the host to port 8085 of the container, and names the container dev-container.
