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
