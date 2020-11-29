# LameTask


################################################################## ON LINUX ###############################################################
#simply run install.sh using : sudo ./install.sh)
#that will : 
#Instal LameLib using
$sudo apt-get install -y lame

#change to project dir and build using 
$cmake .
$make

#run excutable using 
$./bin/CinemoTask ./TestSet



################################################################### ON WINDOWS #########################################################
#install msys and run following commands 
#install gcc
$pacman -S mingw-w64-x86_64-gcc 
#install cmake 
$pacman -S mingw-w64-x86_64-cmake
#add gcc to PATH
$export PATH=$PATH:/mingw64/bin/

## get lame as package installed ##
pacman -S mingw-w64-x86_64-lame-52

#set up compiler paths
export CC=/mingw64/bin/gcc.exe
export CXX=/mingw64/bin/g++.exe

#change to project dir and build using 
$cd ../CinemoTask/LameTask/
$cmake .
$make

#run excutable using 
$./bin/CinemoTask.exe ./TestSet
##########################################################################################################################################
################################################## TO BUILD AND INSTALL LAME LIB FROM SOURCE #############################################
$mkdir lameRepo
$cd lameRepo
$wget https://downloads.sourceforge.net/project/lame/lame/3.100/lame-3.100.tar.gz?r=https%3A%2F%2Fsourceforge.net%2Fprojects%2Flame%2Ffiles%2Flatest%2Fdownload&ts=1606413672
$mv lame-3.100.tar.gz@r=https%3A%2F%2Fsourceforge.net%2Fprojects%2Flame%2Ffiles%2Flatest%2Fdownload lame-3.100.tar.gz
$tar -xvf lame-3.100.tar.gz
$cd lame-3.100/
$./configure
$make
$sudo make install
############################################################################################################################################







