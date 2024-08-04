FROM ubuntu:latest
#Updating the package list
RUN apt-get update

#Installing the essential Tools
RUN apt-get install -y \
    software-properties-common \
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



# Default command
CMD ["tail", "-f", "/dev/null"]



