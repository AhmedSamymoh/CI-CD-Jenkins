What is Google Test?
- Its a specialized library utilized to conduct unit testing in the c++ programming language using a built in test() function.
installing Gtest:
 - you will find all of the required files in this folder https://drive.google.com/drive/folders/1t1mM2IlaMGep2qWd7dnMJBYG_9puzG3r?usp=drive_link
1- Install MinGW 64 kit from the attached link.
2- add cmake/bin , git/bin , mingw64/bin in your environment variables in path
   ![image](https://github.com/user-attachments/assets/6c24c782-8893-4a8b-b960-db9b6cdd43cb)
![image](https://github.com/user-attachments/assets/a476d1da-09f3-4248-afd5-601c54e51fc7)

3- open cmd :
   1- change direction (cd) to  google test folder and type this command { cmake -G "MinGW Makefiles" -B build -DCMAKE_INSTALL_PREFIX=build/output -DBUILD_SHARED_LIBS=ON }
   2- cd build
   3- type : mingw32-make
   4- after it finishes type :mingw32-make install
4- add googletest/build/output/bin in your environment variables in path 
How it works?
- first, paste that function or condition you want to test in a cpp file.
- second, define  
