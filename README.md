# LameTask

## ON LINUX ##
Simply run install.sh using : sudo ./install.sh that will : <br/>
1- Instal LameLib using : <br/>
   $ sudo apt-get install -y lame <br/>
2- Build using : <br/>
   $ cmake . && make <br/>

3- Run excutable using : ./bin/CinemoTask ./TestSet

## ON WINDOWS ##
1- Install msys ,run it , and run following commands :<br/>
2 -Install gcc : <br/>
&nbsp;&nbsp;&nbsp;&nbsp;$ pacman -S mingw-w64-x86_64-gcc <br/>
3- Install cmake : <br/>
&nbsp;&nbsp;&nbsp;&nbsp;$ pacman -S mingw-w64-x86_64-cmake <br/>
4- Add gcc to PATH : <br/>
&nbsp;&nbsp;&nbsp;&nbsp;$ export PATH=$PATH:/mingw64/bin/ <br/>

> ## get lame as package installed <br/>
>  $ pacman -S mingw-w64-x86_64-lame-52 <br/>

6- set up compiler paths: <br/>
&nbsp;&nbsp;&nbsp;&nbsp;$ export CC=/mingw64/bin/gcc.exe <br/>
&nbsp;&nbsp;&nbsp;&nbsp;$ export CXX=/mingw64/bin/g++.exe <br/>

7- change to project dir and build using : <br/>
&nbsp;&nbsp;&nbsp;&nbsp;$ cmake . <br/>
&nbsp;&nbsp;&nbsp;&nbsp;$ make <br/>
8- run excutable using : <br/>
&nbsp;&nbsp;&nbsp;&nbsp;$ ./bin/CinemoTask.exe ./TestSet<br/>

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





