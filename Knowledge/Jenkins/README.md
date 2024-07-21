# Jenkins

## Webhook: Git can communicate with yor Jenkins pipeline 
- `ngrok`: Signing up and Authentication
- Download it and run `ngrok http localhost:8080`
- now get the `Forwarding` link that contain:
    - `http://<subdomin>.ngrok_free.app`
- now open your repo then go to `settings` then `webhook`
- add the url `http://<subdomin>.ngrok_free.app/github-webhook/`

## Authentication with Git
---


Pipeline examples
The examples below were created with the Pipeline Syntax Snippet Generator. Create your own checkout commands with the Pipeline Syntax Snippet Generator configured for your needs.

### Checkout with ssh and a private key credential
Checkout from the git plugin source repository using ssh protocol, ssh private credentials, and the v4.11.x branch. The git plugin supports private key credentials provided by the Jenkins credentials plugin.
```jenkins
checkout scmGit(
    branches: [[name: 'v4.11.x']],
    userRemoteConfigs: [[credentialsId:  'my-ssh-private-key-id',
        url: 'ssh://github.com/jenkinsci/git-plugin.git']])
```

### Checkout with https and a username/password credential
Checkout from the git plugin source repository using https protocol, username/password credentials, and the v4.9.x branch. The git plugin supports username/password credentials provided by the Jenkins credentials plugin.
```jenkins
checkout scmGit(
    branches: [[name: 'v4.9.x']],
    userRemoteConfigs: [[credentialsId: 'my-username-password-id',
        url: 'https://github.com/jenkinsci/git-plugin.git']])
```

### Building C src
---

```jenkins
stage('Build C Program') {
            steps {
                script {
                    try {
                        // Compile the C program
                        bat 'gcc -o main main.c'
                        
                        // Run the compiled program to check for runtime errors
                        bat '.\\main'
                        
                        currentBuild.result = 'SUCCESS'
                    } catch (Exception e) {
                        currentBuild.result = 'FAILURE'
                        error "Build failed: ${e.message}"
                    }
                }
            }
        }

```

