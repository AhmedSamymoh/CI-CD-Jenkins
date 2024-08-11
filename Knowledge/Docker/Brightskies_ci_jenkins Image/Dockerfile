######################################################
######     Dockerized CI Jenkins V1.0 Image     ######
######                                          ######
######               Brightskies                ######
######################################################

# Use the official Jenkins base image
FROM jenkins/jenkins:lts

# Switch to root user to install tools
USER root

# Set the environment variable to avoid prompts during package installation
ENV DEBIAN_FRONTEND=noninteractive

# Update the package list and install necessary packages
RUN apt-get update && \
    apt-get install -y \
    openjdk-17-jdk-headless \
    wget \
    git \
    python3 \
    python3-pip \
    python3-venv \
    curl \
    gnupg2 \
    apt-transport-https \
    build-essential \
    cmake \
    vim \
    lcov \
    cppcheck \
    tree \
	jq \
    && apt-get clean

######################################################    

# Install Google Test
RUN git clone https://github.com/google/googletest.git /usr/src/gtest && \
    cd /usr/src/gtest && \
    cmake . && \
    make && \
    cp lib/*.a /usr/local/lib && \
    cd googletest && \
    cp -r include/gtest /usr/local/include/gtest && \
    cd && \
    rm -rf /usr/src/gtest

######################################################

# Install ngork for tunneling and virtualization of the local server with github
RUN curl -s https://ngrok-agent.s3.amazonaws.com/ngrok.asc \
    | tee /etc/apt/trusted.gpg.d/ngrok.asc >/dev/null \
    && echo "deb https://ngrok-agent.s3.amazonaws.com buster main" \
    | tee /etc/apt/sources.list.d/ngrok.list \
    && apt update \
    && apt install ngrok -y
######################################################

# Add the .devcontainer directory and devcontainer.json file
RUN mkdir -p /var/jenkins_home/.devcontainer
COPY devcontainer.json /var/jenkins_home/.devcontainer/devcontainer.json

# Install Visual Studio Code server
RUN curl -fsSL https://code-server.dev/install.sh | sh

######################################################
# You can add your ngrok token here as it for Ahmed Samy
RUN ngrok config add-authtoken 2jN2HNb3NWPAKWLWPVzUNCltqNH_5mr8HToWoZA36r3bVhhu7

######################################################

# Install Allure Commandline Tool
RUN wget https://github.com/allure-framework/allure2/releases/download/2.14.0/allure-2.14.0.tgz && \
    tar -zxvf allure-2.14.0.tgz -C /opt/ && \
    ln -s /opt/allure-2.14.0/bin/allure /usr/bin/allure

# Create a simple test program to verify Google Test installation
RUN echo '#include <gtest/gtest.h>\n\nTEST(SampleTest, AssertionTrue) {\n    ASSERT_TRUE(true);\n}\n\nint main(int argc, char **argv) {\n    ::testing::InitGoogleTest(&argc, argv);\n    return RUN_ALL_TESTS();\n}' > /tmp/test_gtest.cpp

# Compile and run the test program to verify Google Test installation
RUN g++ -o /tmp/test_gtest /tmp/test_gtest.cpp -lgtest -lgtest_main -pthread && \
    /tmp/test_gtest

# Create a virtual environment and install Pytest
RUN python3 -m venv /opt/venv && \
    /opt/venv/bin/pip install pytest

# Make sure the virtual environment's bin directory is in the PATH
ENV PATH "/opt/venv/bin:$PATH"

# Include Tini for proper process handling
RUN curl -fsSL https://github.com/krallin/tini/releases/download/v0.19.0/tini-static -o /sbin/tini && \
    chmod +x /sbin/tini



# Set Jenkins home
ENV JENKINS_HOME /var/jenkins_home

# Set the entry point to use the Jenkins start script
ENTRYPOINT ["/sbin/tini", "--", "/usr/local/bin/jenkins.sh"]
