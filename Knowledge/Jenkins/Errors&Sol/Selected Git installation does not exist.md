# the problem
Selected Git installation does not exist. Using Default
The recommended git tool is: NONE
using credential Github_PAT3
 > C:\Program Files\Git\bin\git.exe rev-parse --resolve-git-dir C:\ProgramData\Jenkins\.jenkins\workspace\Building_Pipeline@script\e35f77c6df336b72212f5eb54b2ef62e0fb8988b80b41b6b9a7f5318e59c738a\.git # timeout=10
Fetching changes from the remote Git repository
 > C:\Program Files\Git\bin\git.exe config remote.origin.url https://github.com/Ahmedwagdymohy/Building_pipeline # timeout=10
Fetching upstream changes from https://github.com/Ahmedwagdymohy/Building_pipeline
 > C:\Program Files\Git\bin\git.exe --version # timeout=10
 > git --version # 'git version 2.43.0.windows.1'

# The solution:
Make sure that Git is configured inside jenkins by : 
1-go to "Manage Jenkins" 
2- tools
3- scroll to git 
4- make sure that git has the correct path as in your local machine
5- to know the correct path of Git 
6- open CMD , type : where git 
7- copy the path and paste it :) 
