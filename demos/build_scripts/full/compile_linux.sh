
g++ -Wall -g -c sfw.cpp -o sfw.o
g++ -Wall -g -c game_scene.cpp -o game_scene.o
g++ -Wall -g -c main.cpp -o main.o

g++ -Wall -static-libgcc -static-libstdc++ -g sfw.o game_scene.o main.o -lX11 -o game 
