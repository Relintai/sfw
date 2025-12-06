
cp -u ../../tools/merger/out/sfwl_core/sfwl.h sfwl.h
cp -u ../../tools/merger/out/sfwl_core/sfwl.cpp sfwl.cpp

ccache g++ -Wall -g -c sfwl.cpp -o sfwl.o
ccache g++ -Wall -g -c main.cpp -o main.o

#-static-libgcc -static-libstdc++

ccache g++ -Wall -lpthread -static-libgcc -static-libstdc++ -g sfwl.o main.o -o game 

