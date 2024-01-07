
cp -u ../merger/out/sfwl_full/sfwl.h sfwl.h
cp -u ../merger/out/sfwl_full/sfwl.cpp sfwl.cpp

ccache g++ -Wall -g -c sfwl.cpp -o sfwl.o
ccache g++ -Wall -g -c main.cpp -o main.o

#-static-libgcc -static-libstdc++

ccache g++ -Wall -lm -ldl -lpthread -lX11 -g sfwl.o main.o -o game 

