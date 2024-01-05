
ccache g++ -Wall -D_REENTRANT -g -Isfw -c sfw.cpp -o sfw.o

ccache g++ -Wall -D_REENTRANT -g -Isfw -c game_scene.cpp -o game_scene.o
ccache g++ -Wall -D_REENTRANT -g -Isfw -c main.cpp -o main.o


ccache g++ -Wall -lm -ldl -lpthread -lX11  -D_REENTRANT -g sfw.o game_scene.o main.o -o game 

