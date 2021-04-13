@echo off
for /f %%i in ('uuidgen.exe') do set RESULT=%%i
echo -D UUID=\"%RESULT%\"