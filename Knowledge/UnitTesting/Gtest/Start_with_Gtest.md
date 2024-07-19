What is Google Test?
------------------------
- Its a specialized library utilized to conduct unit testing in the c++ programming language using a built in test() function.


installing Gtest:
-------------------
 - you will find all of the required files in this folder : https://mega.nz/folder/sW9mHbIS#7dcdJ405-WBEW-KiJ88Kcw
   
1- Install MinGW 64 kit from the attached link.
2- add cmake/bin , git/bin , mingw64/bin in your environment variables in path
![image](https://github.com/user-attachments/assets/6c24c782-8893-4a8b-b960-db9b6cdd43cb)

3- open cmd :
   1- change direction (cd) to  google test folder and type this command { cmake -G "MinGW Makefiles" -B build -DCMAKE_INSTALL_PREFIX=build/output -DBUILD_SHARED_LIBS=ON }
![image](https://github.com/user-attachments/assets/473659b7-495c-4c6e-a723-3339850078ea)
   
   2- cd build
   3- type : mingw32-make
![image](https://github.com/user-attachments/assets/d1ee4a9a-dd29-43d6-874c-65a3313e259f)



   4- after it finishes type :mingw32-make install
   
![image](https://github.com/user-attachments/assets/35d0ef95-62ae-438e-84c9-a80cc415602e)

4- add googletest/build/output/bin in your environment variables in path 


How it works?
-------------------

   Note, you can use the demo in the folder as a start
   - first, paste that function or condition you want to test in a cpp file.
   - second, define  the test cases of your function using test function provided by google test and write it in a cpp file.
   - don't forget to add the cmakelists file only change the name of the folder in it, look at the image :
   ![image](https://github.com/user-attachments/assets/354be3e8-4c3e-47ec-b4a6-d21e87de584c)
   
   - third build the project , youcan follow these steps to build it :
     
      1- enter the google test folder then build folder then output folder then bin folder copy the directory
            ex:C:\Users\user\Documents\Gtest\googletest\build\output\bin
     
      2- Open cmd , cd to your project file : type this command: cmake -G "MinGW Makefiles" -B build -DGTest_DIR= {use the directory you copied eariler }
           ex:cmake -G "MinGW Makefiles" -B build -DGTest_DIR=C:\Users\user\Documents\Gtest\googletest\build\output\bin
   ![image](https://github.com/user-attachments/assets/db3da366-907d-4c98-9a78-a3bd8ba9f071)
   3- type this command : cmake --build build
   
   ![image](https://github.com/user-attachments/assets/ee96c842-bc7f-4246-9de9-79f65c2c68b6)
   
   4- Finally, now you can run your tests and see the result:
   
   1- cd build 
   
   2- type : runTests.exe
   
   ![image](https://github.com/user-attachments/assets/d9b7affa-67b8-4c71-9c5a-77d7d24df008)












