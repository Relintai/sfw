
clang++ -std=c++14 -g -c sfwl.cpp -o sfwl.o
clang++ -std=c++14 -g -c main.cpp -o main.o

# You might need to add -lpthread and/or -latomic depending on your compiler version

clang++ -std=c++14 -g sfwl.o main.o -o game 
