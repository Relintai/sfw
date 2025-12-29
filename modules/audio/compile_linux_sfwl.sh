
cp -u ../../tools/merger/out/sfwl_full/sfwl.h sfwl.h
cp -u ../../tools/merger/out/sfwl_full/sfwl.cpp sfwl.cpp

ccache g++ -Wall -g -c sfwl.cpp -o sfwl.o
ccache g++ -Wall -g -c audio.cpp -o audio.o
ccache g++ -Wall -g -c main_sfwl.cpp -o main_sfwl.o

#-static-libgcc -static-libstdc++

ccache g++ -Wall -lpthread -static-libgcc -static-libstdc++ -g sfwl.o audio.o main_sfwl.o -o game  

