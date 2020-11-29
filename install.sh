#! /bin/bash
# Download the updated package list for your installed repositories and dependencies to their newest version.
echo -e "\e[92m> Download the updated package list for installed repositories and dependencies to their newest version.\e[39m"
sudo apt-get update
# Instal LameLib using
echo -e "\e[92m> Instal Lame Library\e[39m"
sudo apt-get install lame
# change to project dir and build 
./clean.sh
echo -e "\e[92m> Build the project and produce Executables\e[39m"
cmake .
make
echo -e "\e[92m> Run excutable using  ./bin/CinemoTask ./TestSet :)\e[39m"