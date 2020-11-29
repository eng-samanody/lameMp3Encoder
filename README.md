# LameTask

## ON LINUX ##
Simply run install.sh using : sudo ./install.sh that will : 
1- Instal LameLib using : sudo apt-get install -y lame
2- Build using : cmake . && make

3- Run excutable using : ./bin/CinemoTask ./TestSet

## ON WINDOWS ##
1- Install msys ,run it , and run following commands :<br/>
2 -Install gcc : <br/>
  $ pacman -S mingw-w64-x86_64-gcc <br/>
3- Install cmake : <br/>
  $ pacman -S mingw-w64-x86_64-cmake <br/>
4- Add gcc to PATH : <br/>
  $ export PATH=$PATH:/mingw64/bin/ <br/>

> ## get lame as package installed <br/>
$pacman -S mingw-w64-x86_64-lame-52 <br/>

6- set up compiler paths: <br/>
  $ export CC=/mingw64/bin/gcc.exe <br/>
  $ export CXX=/mingw64/bin/g++.exe <br/>

7- change to project dir and build using : <br/>
  $ cmake .
  $ make
8- run excutable using : <br/>
  $ ./bin/CinemoTask.exe ./TestSet

> ## TO BUILD AND INSTALL LAME LIB FROM SOURCE 
>$ mkdir lameRepo <br/>
$ cd lameRepo<br/>
$ wget https://downloads.sourceforge.net/project/lame/lame/3.100/lame-3.100.tar.gz?r=https%3A%2F%2Fsourceforge.net%2Fprojects%2Flame%2Ffiles%2Flatest%2Fdownload&ts=1606413672 <br/> or download lame library source from : https://lame.sourceforge.io/download.php <br/> 
$ mv lame-3.100.tar.gz@r=https%3A%2F%2Fsourceforge.net%2Fprojects%2Flame%2Ffiles%2Flatest%2Fdownload lame-3.100.tar.gz <br/>
$ tar -xvf lame-3.100.tar.gz <br/>
$ cd lame-3.100/ <br/>
$ ./configure <br/>
$ make <br/>
$ sudo make install





