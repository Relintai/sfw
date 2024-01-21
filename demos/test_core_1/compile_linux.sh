
ccache g++ -Wall -g -c sfw.cpp -o sfw.o
ccache g++ -Wall  -g -c main.cpp -o main.o

#-static-libgcc -static-libstdc++

ccache g++ -Wall -lm -ldl -lpthread -lX11 -g sfw.o main.o -o game 

