
g++ -Wall -g -c sfwl.cpp -o sfwl.o
g++ -Wall -g -c main.cpp -o main.o

# You might need to add -lpthread and/or -latomic depending on your compiler version

g++ -Wall -g sfwl.o main.o -lShlwapi -lws2_32 -o game 
