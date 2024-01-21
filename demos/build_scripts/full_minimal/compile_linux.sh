
g++ -Wall -g -c sfw.cpp -o sfw.o
g++ -Wall -g -c main.cpp -o main.o

g++ -Wall -static-libgcc -static-libstdc++ -g sfw.o main.o -lX11 -o game 
