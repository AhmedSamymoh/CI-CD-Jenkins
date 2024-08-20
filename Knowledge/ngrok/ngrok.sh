#!/bin/bash


#@ Don't map 8080 to your maped port like 8083 make it what can docker container can access JENKINS_PORT
ngrok http 8080 --log=stdout > newsubdomain.txt &

echo "============================================================================================="
echo "Ngrok tunnel is created"
echo "============================================================================================="
echo "Enabling Automated webhooks with github api"

sleep 3

#pip3 install requests -y 

python3 webhook.py
echo "============================================================================================="
echo "======================================== Done =============================================="
echo "============================================================================================="