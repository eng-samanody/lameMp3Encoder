#! /bin/bash
echo -e "\e[92m>Removing old build cache\e[39m"
rm -rf ./CMakeFiles
rm cmake_install.cmake
rm Makefile
rm CMakeCache.txt
rm ./TestSet/*.mp3

