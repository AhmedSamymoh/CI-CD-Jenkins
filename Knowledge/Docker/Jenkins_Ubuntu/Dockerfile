# Use the latest Ubuntu base image
FROM ubuntu:latest

# Set the environment variable to avoid prompts during package installation
ENV DEBIAN_FRONTEND=noninteractive

# Update the package list and install necessary packages
RUN apt-get update && \
    apt-get install -y \
    openjdk-21-jdk \
    wget \
    software-properties-common\
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

# Install Jenkins
RUN curl -fsSL https://pkg.jenkins.io/debian/jenkins.io.key | apt-key add - && \
    sh -c 'echo deb http://pkg.jenkins.io/debian-stable binary/ > /etc/apt/sources.list.d/jenkins.list' && \
    apt-get update && \
    apt-get install -y jenkins && \
    apt-get clean

# Install Google Test
RUN git clone https://github.com/google/googletest.git /usr/src/gtest && \
    cd /usr/src/gtest && \
    git checkout $(git describe --tags) && \
    cmake . && \
    make && \
    make install && \
    cd && \
    rm -rf /usr/src/gtest

# Create and activate virtual environment, then install Pytest
RUN python3 -m venv /opt/venv && \
    /opt/venv/bin/pip install --upgrade pip && \
    /opt/venv/bin/pip install --upgrade pytest



# Install MinGW64
RUN apt-get update && apt-get install -y \
    mingw-w64 \
    && rm -rf /var/lib/apt/lists/*


#install CppCheck
RUN apt-get update && apt-get install -y \
    cppcheck \
    && rm -rf /var/lib/apt/lists/*



# Install Allure 2.30
RUN wget https://github.com/allure-framework/allure2/releases/download/2.30.0/allure-2.30.0.zip && \
    unzip allure-2.30.0.zip -d /opt && \
    ln -s /opt/allure-2.30.0/bin/allure /usr/bin/allure && \
    rm allure-2.30.0.zip


# Make the virtual environment available in the PATH
ENV PATH="/opt/venv/bin:$PATH"

# Expose the Jenkins port
EXPOSE 8085

# Set Jenkins home
ENV JENKINS_HOME=/var/lib/jenkins

# Override the default Jenkins port
RUN sed -i 's/HTTP_PORT=8080/HTTP_PORT=8085/' /etc/default/jenkins

# Start Jenkins using the service command and keep the container running
CMD ["sh", "-c", "service jenkins start && tail -f /var/log/jenkins/jenkins.log"]
