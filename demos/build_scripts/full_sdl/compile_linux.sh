
export sdlargs=$(pkg-config --cflags sdl3)
export sdlargslink=$(pkg-config --cflags --libs sdl3)

g++ -Wall -g -c sfw_sdl.cpp -o sfw_sdl.o
g++ -Wall -g -c game_scene.cpp -o game_scene.o
g++ -Wall -g -c main.cpp -o main.o

g++ -Wall -static-libgcc -static-libstdc++ -g sfw_sdl.o game_scene.o main.o -lX11 $sdlargslink -o game 
