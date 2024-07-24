# GTest

```batch
 g++ -I"O:/01. Programs/GTest/googletest/build/output/include" -L"O:/01. Programs/GTest/googletest/build/output/lib" .\Calc.c .\Calctest.cpp -lgtest -lgtest_main -pthread
```
```batch
git rev-parse --abbrev-ref HEAD
git branch -a

set PATH=%PATH%;O:\01. Programs\GTest\googletest\build\output\lib

g++ -I"O:/01. Programs/GTest/googletest/build/output/include" -L"O:/01. Programs/GTest/googletest/build/output/lib" .\Calc.c .\Calctest.cpp -lgtest -lgtest_main -pthread 

a.exe
```
```
```batch
@echo off
setlocal

REM Debugging: Print the current directory
echo Current Directory: %cd%

REM Debugging: Print the PATH variable before modification
echo Initial PATH: %PATH%

REM Add the GTest library path to the system PATH
set PATH=%PATH%;O:\01. Programs\GTest\googletest\build\output\lib

REM Debugging: Print the PATH variable after modification
echo Modified PATH: %PATH%

REM Verify presence of required DLLs
if not exist "O:\01. Programs\GTest\googletest\build\output\lib\libgtest.dll" (
    echo libgtest.dll not found!
    exit /b 1
)
if not exist "O:\01. Programs\GTest\googletest\build\output\lib\libgtest_main.dll" (
    echo libgtest_main.dll not found!
    exit /b 1
)

REM Debugging: List the files in the directory to confirm presence
echo Listing files in O:\01. Programs\GTest\googletest\build\output\lib:
dir "O:\01. Programs\GTest\googletest\build\output\lib"

REM Compile the source code
echo Compiling with g++...
g++ -I"O:/01. Programs/GTest/googletest/build/output/include" -L"O:/01. Programs/GTest/googletest/build/output/lib" .\Calc.c .\Calctest.cpp -lgtest -lgtest_main -pthread
if %errorlevel% neq 0 (
    echo Compilation failed!
    exit /b %errorlevel%
)

REM Run the executable
echo Running the executable...
a.exe
if %errorlevel% neq 0 (
    echo Executable failed with error code %errorlevel%!
    exit /b %errorlevel%
)

endlocal
a.exe
```
