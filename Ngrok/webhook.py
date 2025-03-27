#!/opt/venv/bin/ python3
import re
import requests

#============================== Developer Configurations ==================================
GITHUB_API_URL = "https://api.github.com"
REPO_OWNER = "AhmedSamymoh"  # Your GitHub username
REPO_NAME = "AUTOSAR_SPI_Handler"  # Your GitHub repo name
GITHUB_TOKEN = "*************"  # Your GitHub token
#===========================================================================================

# Read the content of newsubdomain.txt to get the ngrok URL
with open('newsubdomain.txt', 'r') as file:
    content = file.read()

ngrok_url = re.search(r'https://[a-zA-Z0-9-]*\.ngrok-free\.app', content)

if ngrok_url:
    base_url = ngrok_url.group(0)

    # Webhook 1: Pull Request
    pr_payload = {
        "name": "web",
        "active": True,
        "events": ["pull_request"],
        "config": {
            "url": f"{base_url}/ghprbhook/",
            "content_type": "json",
            "insecure_ssl": "0"  # Set to "1" to disable SSL verification
        }
    }

    # Webhook 2: Push
    push_payload = {
        "name": "web",
        "active": True,
        "events": ["push"],
        "config": {
            "url": f"{base_url}/multibranch-webhook-trigger/invoke?token=my-token",
            "content_type": "json",
            "insecure_ssl": "0"  # Set to "1" to disable SSL verification
        }
    }

    # Create the pull request webhook
    pr_response = requests.post(
        f"{GITHUB_API_URL}/repos/{REPO_OWNER}/{REPO_NAME}/hooks",
        json=pr_payload,
        headers={
            "Authorization": f"token {GITHUB_TOKEN}",
            "Accept": "application/vnd.github.v3+json"
        }
    )

    # Create the push event webhook
    push_response = requests.post(
        f"{GITHUB_API_URL}/repos/{REPO_OWNER}/{REPO_NAME}/hooks",
        json=push_payload,
        headers={
            "Authorization": f"token {GITHUB_TOKEN}",
            "Accept": "application/vnd.github.v3+json"
        }
    )

    # Check the results for the pull request webhook
    if pr_response.status_code == 201:
        print("Pull request webhook created successfully.")
        print(f"Webhook details: {pr_response.json()}")
    else:
        print(f"Failed to create pull request webhook: {pr_response.status_code} {pr_response.text}")

    # Check the results for the push event webhook
    if push_response.status_code == 201:
        print("Push event webhook created successfully.")
        print(f"Webhook details: {push_response.json()}")
    else:
        print(f"Failed to create push event webhook: {push_response.status_code} {push_response.text}")

else:
    print("Ngrok URL not found.")
