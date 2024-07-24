# Integrating Jenkins with Email Notifications

This guide will walk you through the steps required to configure Jenkins to send email notifications using your email settings.

## Steps to Configure Email Notifications in Jenkins

## Important note
If your email is Gmail, you need to create an application password for Jenkins specifically and use this password as your email password. This is necessary because Gmail often requires application-specific passwords for third-party applications like Jenkins.

### Step 1: Configure SMTP Settings

1. **Navigate to Manage Jenkins**:
   - Go to your Jenkins dashboard.
   - Click on `Manage Jenkins` from the left-hand menu.

2. **Configure System Settings**:
   - Click on `Configure System`.
   - Scroll down to the `Extended E-mail Notification` section.

3. **Set Up SMTP Server**:
   - **SMTP server**: `smtp.gmail.com`
   - **SMTP Port**: `465`
   - **Use SSL**: Check this box.
   - **Credentials**: Add your email credentials (ensure you use an App Password if 2-Step Verification is enabled).

![alt text](<Screenshot 2024-07-24 at 12.55.47 PM.png>)   

4. **Default Settings**:
   - **Default user e-mail suffix**: `@gmail.com`
   ![alt text](<Screenshot 2024-07-24 at 12.55.28 PM.png>)
5. **Test Configuration**:
   - Use the `Test configuration by sending test e-mail` button to verify your settings.

   ![alt text](<Screenshot 2024-07-24 at 12.56.09 PM.png>)

### Step 2: Configure Job to Send Email Notifications

1. **Navigate to Job Configuration**:
   - Go to your job in Jenkins (e.g., `test-job`).
   - Click on `Configure`.

2. **Add Post-build Action**:
   - Scroll down to the `Post-build Actions` section.
   - Click on `Add post-build action`.
   - Select `E-mail Notification`.

3. **Configure Email Notification**:
   - **Recipients**: Enter the email addresses separated by spaces or commas (e.g., `ahmeds.elnozahy@gmail.com mohamedcherif03@gmail.com`).
   - **Send e-mail for every unstable build**: Check this box if you want to receive notifications for unstable builds.
   

  ![alt text](<Screenshot 2024-07-24 at 12.57.24 PM.png>)

4. **Editable Email Notification**:
   - You can also use the "Editable Email Notification" for more customization.
   - **Project Recipient List**: Ensure recipients are listed correctly, separated by commas. For example: `ahmeds.elnozahy@gmail.com, mohamedcherif03@gmail.com`
   - Customize the subject and content if needed.

   ![alt text](<Screenshot 2024-07-24 at 12.57.45 PM.png>)

5. **Save Configuration**:
   - Click on `Save` to apply the changes.

### Step 3: Create and Test a Pipeline with Email Notification

Use the following example pipeline script to test email notifications with retry logic:

```groovy
pipeline {
    agent any
     
    stages {
        stage('Test Stage') {
            steps {
                echo "Testing email notification"
            }
        }
    }
    post {
        always {
            script {
                def maxRetries = 2
                def retryCount = 0
                def emailSent = false

                while (retryCount < maxRetries && !emailSent) {
                    try {
                        emailext(
                            body: 'This is a test email from Jenkins',
                            subject: 'Jenkins Test Email',
                            to: 'ahmeds.elnozahy@gmail.com, mohamedcherif03@gmail.com'
                        )
                        emailSent = true
                        echo "Email sent successfully on attempt ${retryCount + 1}"
                    } catch (Exception e) {
                        retryCount++
                        if (retryCount < maxRetries) {
                            echo "Connection error sending email, retrying in 10 seconds... (${retryCount}/${maxRetries})"
                            sleep(time: 10, unit: 'SECONDS')
                        } else {
                            echo "Failed after ${maxRetries} attempts to send email"
                        }
                    }
                }

                if (!emailSent) {
                    error "Email sending failed after ${maxRetries} attempts"
                }
            }
        }
    }
}
![alt text](<Screenshot 2024-07-24 at 12.35.28 PM.png>) ![alt text](<Screenshot 2024-07-24 at 12.25.31 PM.png>) ![alt text](<Screenshot 2024-07-24 at 12.25.19 PM.png>)