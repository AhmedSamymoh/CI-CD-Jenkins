@echo off
rem Create test_results folder if it doesn't exist
if not exist test_results (
    mkdir test_results
)

rem Compile C code into shared libraries
echo Compiling C code...
gcc -shared -o module1.so -fPIC module1.c
gcc -shared -o module2.so -fPIC module2.c

rem Run pytest and output reports to test_results folder
echo Running tests...
pytest --cov=your_module --cov-branch --cov-report=html:test_results/cov_report.html --junitxml=test_results/report.xml --html=test_results/report.html

rem Generate HTML coverage report from .coverage file
coverage html -d test_results/htmlcov


echo Done.
read -p "Press any key to Exit..."