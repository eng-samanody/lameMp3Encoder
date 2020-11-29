#! /bin/bash
# Download the updated package list for your installed repositories and dependencies to their newest version.
sudo apt-get update
# Instal LameLib using
sudo apt-get install lame
# change to project dir and build 
cmake .
make
echo run excutable using  ./bin/CinemoTask ./TestSet