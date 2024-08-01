# Allure configuration
- Install allure plugin from jenkins
- Configure commandline from the path directory you are in


![image](https://github.com/user-attachments/assets/1be7339c-8b5a-4155-ae65-dc36feebb934)


  
-----------------------------------------------------------------------------------------


# Building allure in pytest

- this command, Pytest will execute your test cases and save the test results in the allure-results in batch file

      "C:\\Users\\Rana\\AppData\\Local\\Programs\\Python\\Python312\\Scripts\\pytest.exe" --alluredir=allure-results
  Explanation:
  1- "C:\Users\Rana\AppData\Local\Programs\Python\Python312\Scripts\pytest.exe":

    This is the full path to the pytest executable. In this case, it is located in the Python installation directory on your system.
    The double backslashes (\\) are used to escape backslashes in Windows file paths.


  2- --alluredir=allure-results:

    This option tells Pytest to save the Allure results in the allure-results directory.
    --alluredir is a Pytest option provided by the allure-pytest plugin to specify the output directory for Allure test results.
    

![image](https://github.com/user-attachments/assets/dec299c0-4b18-48f0-b411-3e3bafe261ff)





- Add this stage in pipeline stages

      stage('Generate Allure Report') {
            steps {
                allure includeProperties: true, jdk: '', results: [[path: 'alluree/allure-results']]
            }
        }
![image](https://github.com/user-attachments/assets/d3fe88a1-3223-4d1e-8b14-5cdfb82ff31d)



![image](https://github.com/user-attachments/assets/e4e0e6c9-74e6-4346-82a8-d165bde7f371)




![image](https://github.com/user-attachments/assets/75faffc4-6450-43cd-a2ed-024dd491b987)











