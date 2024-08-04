FROM ubuntu:latest

# Update package lists
RUN apt update && apt upgrade -y

# Install Java (Jenkins requires Java)
RUN apt install -y default-jdk

# Install wget for downloading Jenkins installation script
RUN apt install -y wget

# Download and install Jenkins
RUN wget -O /tmp/jenkins.war https://get.jenkins.io/war-stable/latest/jenkins.war \
    && java -jar /tmp/jenkins.war --httpPort=8080 &


# Expose Jenkins port
EXPOSE 8080



CMD ["tail", "-f", "/dev/null"]
