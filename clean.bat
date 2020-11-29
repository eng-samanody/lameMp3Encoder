@echo off
echo Removing old build cache
rmdir /S .\CMakeFiles
del cmake_install.cmake
del Makefile
del CMakeCache.txt
del .\TestSet\*.mp3

PAUSE