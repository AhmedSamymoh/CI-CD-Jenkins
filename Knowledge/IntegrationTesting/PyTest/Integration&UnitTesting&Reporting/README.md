# Creating Unit Testing and Integration testing with pytest for C/C++

#### Prerequisites
Before you begin, ensure you have the following tools installed:
- GCC (GNU Compiler Collection)
- Python (with pytest, pytest-cov, pytest-html, and coverage.py packages)
You can install the necessary Python packages using pip:

```bash
pip install pytest pytest-cov pytest-html coverage
```
Project Structure
```markdown
your_project/
│
├── module1.c
├── module1.h
├── module2.c
├── module2.h
└── binding.py
│
├── tests/
│   ├── test_module1.py
│   ├── test_module2.py
│   └── test_integration.py
│
├── run_tests.bat
└── pytest.ini
```

#### You can download the files from the repo and continue the steps with me 
#### You can also skip the guide and run the bat script, it will automate all the steps

-   Compile the C code to generate the shared Library
```bash
gcc -shared -o module1.so -fPIC module1.c
gcc -shared -o module2.so -fPIC module2.c
```

-   Run pytest and output reports to test_results folder
```bash
pytest --cov=your_module --cov-branch --cov-report=html:test_results/cov_report.html --junitxml=test_results/report.xml --html=test_results/report.html
```


# Automation using bat file :
Creating a batch (`.bat`) file to automate the process of building your C code, running tests, and saving the results in a specified folder can streamline your workflow. Here's a step-by-step guide to creating such a script:

### 1. Create the Batch File

Create a new file named `run_tests.bat` and open it in a text editor. 

### 2. Add Commands to Create Test Folder

Add commands to create a `test_results` folder if it doesn't already exist.

```bat
@echo off
if not exist test_results (
    mkdir test_results
)
```

### 3. Compile the C Code

Add commands to compile your C code into shared libraries using GCC.

```bat
@echo off
if not exist test_results (
    mkdir test_results
)

echo Compiling C code...
gcc -shared -o test_results/module1.dll -fPIC module1.c
gcc -shared -o test_results/module2.dll -fPIC module2.c
```

### 4. Run Pytest

Add commands to run `pytest` with the desired options and output the results to the `test_results` folder.

```bat
@echo off
if not exist test_results (
    mkdir test_results
)

echo Compiling C code...
gcc -shared -o test_results/module1.dll -fPIC module1.c
gcc -shared -o test_results/module2.dll -fPIC module2.c

echo Running tests...
pytest --cov=your_module --cov-branch --cov-report=html:test_results/cov_report.html --junitxml=test_results/report.xml --html=test_results/report.html
```

### Full `run_tests.bat` Script

Here's the complete script:

```bat
@echo off
rem Create test_results folder if it doesn't exist
if not exist test_results (
    mkdir test_results
)

rem Compile C code into shared libraries
echo Compiling C code...
gcc -shared -o test_results/module1.dll -fPIC module1.c
gcc -shared -o test_results/module2.dll -fPIC module2.c

rem Run pytest and output reports to test_results folder
echo Running tests...
pytest --cov=your_module --cov-branch --cov-report=html:test_results/cov_report.html --junitxml=test_results/report.xml --html=test_results/report.html

rem Indicate script completion
echo Done.
```

### Running the Batch File

1. Place `run_tests.bat` in the root directory of your project (where `module1.c`, `module2.c`, and your Python test scripts are located).
2. Open a command prompt and navigate to the project directory.
3. Run the batch file:
   ```bat
   run_tests.bat
   ```

This script will:

1. Create a `test_results` folder if it doesn't exist.
2. Compile the C code into shared libraries and place them in the `test_results` folder.
3. Run `pytest` with the specified options and save the reports in the `test_results` folder.
4. Indicate the script has completed.

### Summary

This batch file automates the entire process of building your C code, running tests, and saving the results in a specified folder. It simplifies your workflow and ensures consistent execution of your build and test process. Let me know if you need further customization or assistance!
