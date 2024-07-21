CMake 
-------------
- A powerful tool that creates Makefiles that can manipulate your program in every way.
- writing a cmakelists file that runs using cmake tool then a Makefile is created
- CMake is easier to deal or write than Makefiles directily

Documentation:    https://cmake.org/cmake/help/latest/index.html
 -------------------------------------------------

CMake functions:
--------------------------
1- cmake_minimum_required(VERSION 3.22)

2- project(cmake)  //the name of the folder

3- add_executable(hellobinary main.cpp src/calc.cpp)

4- target_include_directories(hellobinary PUBLIC include/)

5- set(src_file main.cpp src/calc.cpp)
---> add_executable(hellobinary ${src_file})

6- message("source file has ${src_file}")
      - STATUS
      - WARNING
      - FATAL_ERROR
7- cmake --help

         --help-command <cmd> [<file>]= Print help for one command and exit.
         --help-command-list [<file>] = List commands with help available and exit

 8- IF and ELSE conditions

 9- Inheritance 

 10- add_subdirectory(${CMAKE_SOURCE_DIR}/lib)

11- add_library ---> creates library

12- target_link_libraries

13- Configure file :can be used to generate header file

-------------------------------------------------------------------------------------------


- Cmake variables


--------------------------------------------------------------

 - Cmake If , Foreach


-------------------------------


- Cmake Function , Cache
   - Variadic Function 

------------------------------------------------
  
