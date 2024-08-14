# Google Test

## Allure with Gtest:

```bat
cmake -G "MinGW Makefiles" -B build -DGTest_DIR=$env:GTEST_DIR
```
```bat
cmake --build build
```
```bat
cd build
```
```bat
sample_test.exe --gtest_output=xml:report.xml
```
```bat
mkdir allure-results
move report.xml allure-results
```
```bat
allure generate allure-results --clean -o allure-report
```
```bat
allure open allure-report
```
