# Code Coverage

## Intrudction
 How do we know we have tested out code well?\
 One measure is that we have executed each code statement at least once.\
 Code Coverage tools, like gcov, help us know which lines of the code have been executed (and
 how many times)\
 Quality metrics and customer agreements often demand close to 100% code coverage reports\


-----------------------------------------------------------------------------------------------------

## Using GCC compiler
- To Make the code coverage you will have to install ' GCC ' compiler

- suppose we have a main.c file and we want to see the code coverge of it
```bash
gcc -fprofile-arcs -ftest-coverage main.c
#Replace main.c with your C file
```
- It will show (.out) file and (.gnco) file

- ![image](https://github.com/user-attachments/assets/1367b45b-e5dd-4093-bad6-df193b17d887)


- Let us now run a test case
```bash
./a.out
gcov main.c
#It will show the result of the code Coverage
```
- Note that file (main.c.gcov) has been created
- If we open it It will show all the details about the coverage\
![image](https://github.com/user-attachments/assets/6d0c631d-5c68-41f9-bcb9-eeb8abb5cacc)

  
#### The first column indicates how many times a line is excuted. it might have :
  -   a number : indicates how many times the line got excuted
  -   '-' : indicates that the line is not an executable statement
  -  '#####' : indicates that the line is not excuted yet 
------------------------------------------------------------------------------------------------------------
## Notes
 1. Do not use optimization options while using code coverage. That changes source code
 line number to machine code mapping adversely
 2. Running the executable just updates “.gcda” files. The “.c.gcov” has to be generated
 manually for each source code file by doing “gcov <file.c>”.\
 This command correlates the
structural information in “.gcno” file with data information in “.gcda” file, to generate
 textual report in “.c.gcov” file

## To know the Number of branches in the code :
1- Suppose we have two files `main.c` and `calc.c` 
Compile Both Files with Coverage Flags

2- Compile your `calc.c` and `main.c` files with coverage flags. Make sure to link them together.


```sh
gcc -fprofile-arcs -ftest-coverage -o calc main.c calc.c  
``` 


 

3- Run the generated executable to produce the coverage data files (.gcda and .gcno).

```sh
./calc
```



# Create GUI Reports for Code Coverage
#### Using `lcov` on Windows with MSYS2

### Installation

> **Warning**  
> Using lcov on Windows can be a bit challenging because it's primarily designed for Unix-like systems. However, you can set it up using a combination of Cygwin or MSYS2, which provide Unix-like environments on Windows.

### Steps to Install and Use `lcov`:

1. **Install MSYS2:**
   - Download the MSYS2 installer from the [MSYS2 website](https://www.msys2.org/).
   - Run the installer and follow the installation instructions.

2. **Update MSYS2 Packages:**
   - Open the MSYS2 shell (`MSYS2 MinGW 64-bit` or `MSYS2 MinGW 32-bit` depending on your system architecture).
   - Update the package database and core system packages by running:
     ```sh
     pacman -Syu
     ```
   - Restart the MSYS2 shell after the update.

3. **Install Required Packages:**
   - Install GCC, gcov, lcov, and other essential tools by running:
     ```sh
     pacman -S base-devel mingw-w64-x86_64-toolchain lcov
     ```

4. **Compile Your Code with Coverage Flags:**
   - Open the MSYS2 MinGW shell (`MSYS2 MinGW 64-bit` or `MSYS2 MinGW 32-bit`).
   - Navigate to your project directory.
   - Compile your code with `-fprofile-arcs` and `-ftest-coverage` flags:
     ```sh
     gcc -fprofile-arcs -ftest-coverage -o calc calc.c
     ```

5. **Run Your Executable:**
   - Run the compiled executable to generate coverage data files (.gcda and .gcno):
     ```sh
     ./calc
     ```

6. **Generate Coverage Data with lcov:**
   - Capture the coverage data:
     ```sh
     lcov --capture --directory . --output-file calc.info
     ```
   - This will create a `calc.info` file containing the coverage data.

7. **Generate HTML Report with genhtml:**
   - Generate an HTML report from the `calc.info` file:
     ```sh
     genhtml calc.info --output-directory out
     ```

8. **View the HTML Report:**
   - Open the `index.html` file in the `out` directory using any web browser to view the coverage report.

By following these steps, you can successfully generate GUI reports for code coverage using `lcov` on Windows.
