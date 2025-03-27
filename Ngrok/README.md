# Ngrok Webhook Automation for Jenkins & GitHub

This setup automates the creation of GitHub webhooks using Ngrok to expose a local Jenkins instance to the internet.

## Prerequisites
- **Docker** (if running Jenkins in a container)
- **Ngrok** (installed and authenticated)
- **Python 3**
- **`requests` library** (install using `pip install requests`)
- **GitHub Personal Access Token** (PAT) with `admin:repo_hook` permissions

## Usage

1. **Run the script**
```sh
   ./ngrok.sh
```

This will:
- Start an Ngrok tunnel on port `8080`
- Extract the public URL
- Call `webhook.py` to configure GitHub webhooks for push and pull request events

## Verify Webhooks in GitHub
- Navigate to `Settings -> Webhooks` in your repository
- Ensure the newly created webhooks are listed and pointing to the Ngrok URL

## Configuration
Update `webhook.py` with your GitHub repository details:

```python
REPO_OWNER = "AhmedSamymoh"  # Your GitHub username
REPO_NAME = "AUTOSAR_SPI_Handler"  # Your GitHub repository
GITHUB_TOKEN = "*************"  # Your GitHub PAT
```

## Notes
- Do **not** expose your GitHub token publicly.
- Ngrok URLs change on every restart; rerun `ngrok.sh` to update webhooks.
- To make Ngrok use a static domain, upgrade to a paid plan.

## Troubleshooting
- If webhooks fail, check the Ngrok logs:

```sh
  cat newsubdomain.txt
```

- Verify your GitHub token has the required permissions.



