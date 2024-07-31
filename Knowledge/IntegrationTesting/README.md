# Setting up pyTest with C/C++
-   Make a `.c` file & `.py` file
-   In `.c` file write your function inside it
-   To get the shared library file run :
```bash
gcc -shared -o mylib.so main.c
```
-   In `.py` file make sure that you have the following setup
```python
import ctypes
# Load the shared library
# sharedLibrary is just a variable name :) you can change it later
SharedLibrary = ctypes.CDLL("C:\\Users\\study\\OneDrive\\Desktop\\pyTest\\mylib.so")
```
-   To use the function written in C using python
```python
SharedLibrary."functionName"()
```