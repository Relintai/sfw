
g++ -Wall -g -c sfwl.cpp -o sfwl.o
g++ -Wall -g -c main.cpp -o main.o

g++ -Wall -static-libgcc -static-libstdc++ -g sfwl.o main.o -o game 
