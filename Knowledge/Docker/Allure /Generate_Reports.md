# How to generate Allure reports inside jenkins in Docker container

# Overview
- This project includes a Jenkins pipeline to automate the testing process using pytest and generate test reports with Allure. The pipeline is divided into two main stages:

1- Run pytest: Compiles C code into shared libraries, runs the tests, and stores the test results.


2- Generate Allure Report: Generates and publishes the Allure test report based on the test results.


---------------------------------------------------------------------------------------------



1- Download allure plugin in jenkins

2- Configure Allure commandline 
- Inside manage jenkins enter tools scroll down


- ![image](https://github.com/user-attachments/assets/08dcf7a3-a14e-46f7-a9bf-630d03da1ff2)


3- Specify the Allure tool in the pipeline script :


![image](https://github.com/user-attachments/assets/32212cc9-a975-4f32-87c4-3cdb5468dbba)


## OPTIONAL

You can do some debugging to check files availabilty and accessability

     stage('Setup') {
                steps {
                    // Ensure the script is executable
                    sh 'chmod +x alluree/binding.py'
                }
            }
            stage('Debug') {
                steps {
                    // Debug the file path
                    sh '''
                    echo "Current Directory:"
                    pwd
                    echo "Listing Files:"
                    ls -l
                    echo "Listing Files in alluree:"
                    ls -l alluree
                    '''
                }
            }

## Note its very very important to accuratly place your files in the repo  
## (Any mistake or conflict will result in errors or no report I can gaurante that after hunderds of modifications)


Here is How i did it 

![Screenshot 2024-08-07 012022](https://github.com/user-attachments/assets/a432e93c-1509-4a8f-b853-44bff35046c3)



----------------------------------------------------------------------------------------------------------



4- Run Pytest in jenkinsfile :


1- Stage 1:  This stage performs the following tasks:

- Navigate to alluree Directory: Changes the working directory to alluree.
- Compile C Code: Compiles C code files (module1.c and module2.c) into shared libraries (.so and .dll).
- Run pytest: Executes the pytest tests and outputs the results to the test_results folder.


      
      # Create test_results folder if it doesn't exist
      cd alluree
      
      # Compile C code into shared libraries
      echo "Compiling C code..."
      export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:.
      gcc -shared -o module1.so -fPIC module1.c
      gcc -shared -o module2.so -fPIC module2.c
      gcc -shared -o module1.dll -fPIC module1.c
      gcc -shared -o module2.dll -fPIC module2.c
      
      # Run pytest and output reports to test_results folder
      echo "Running tests..."
      /opt/venv/bin/pytest binding.py || true
      echo "Done."




2-  Stage 2: Generate Allure Report
This stage performs the following tasks:

- Generate Allure Results: Runs pytest with the Allure results directory specified.
- Publish Allure Report: Uses the allure Jenkins plugin to include the generated Allure results.

      export PATH=$PATH:/usr/bin 
      cd alluree
      python3 -m pytest --alluredir allure-results
      allure includeProperties: true, jdk: '', results: [[path: 'alluree/allure-results']]



----------------------------------------------------------------------------------------------------




# Results:


Jenkins pipeline overview :


![image](https://github.com/user-attachments/assets/fcb53bd6-4671-4441-b378-cb7074ea3de3)



Jenkins console output :

![image](https://github.com/user-attachments/assets/8fd86bb3-9290-42c0-82e3-44ae6ac33cb3)


Allure Report:


![image](https://github.com/user-attachments/assets/2ebb10a4-691f-41dc-bbb1-b4985a1faedf)





