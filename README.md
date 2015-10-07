# Virustotal

[Imgur](http://i.imgur.com/D3tOhml.png?1)

** feel free to fork and help me code better **

# Pre Compiling

* For compiling on one of my windows 10 machines i used mingw downloadable <a href="http://sourceforge.net/projects/mingw/files/">here</a>

* After that do not forget to add C:\MinGW\bin; to the PATH environment variable in windows

* And then finally you can compile.

# Compiling

Navigate to your directory there you will see "main.cpp" this is your main codez file. After that you can think of a nice name you want to give your progam like "keymaster.exe". So if you want to compile this you will need to use this line below:

`g++ -Wl,-subsystem,windows main.cpp -o keymaster.exe`

Why you may ask? Well this is because we need to have a linker that remembers us to not make a console application but a windows application for hiding your window.
