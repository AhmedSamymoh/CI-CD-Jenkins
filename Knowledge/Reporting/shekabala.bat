@echo off
setlocal

:: Set the path to the MSYS2 installation directory
set MSYS2_PATH="C:\msys64"



:: Call the Bash script using MSYS2
%MSYS2_PATH%\mingw64.exe .\shekabala.sh


endlocal
pause