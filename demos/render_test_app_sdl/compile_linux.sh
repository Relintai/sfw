#cp -u ../../tools/merger/out/full/sfw.h sfw.h
#cp -u ../../tools/merger/out/full/sfw.cpp sfw.cpp
#cp -u ../../tools/merger/out/full/sfw_3rd.m sfw_3rd.m


export sdlargs=$(pkg-config --cflags sdl3)
export sdlargslink=$(pkg-config --cflags --libs sdl3)

ccache g++ -Wall -g $sdlargs -c sfw_sdl.cpp -o sfw_sdl.o
ccache g++ -Wall -g $sdlargs -c game_scene.cpp -o game_scene.o
ccache g++ -Wall -g $sdlargs -c main.cpp -o main.o

ccache g++ -Wall -static-libgcc -static-libstdc++ -g sfw_sdl.o game_scene.o main.o -lX11 $sdlargslink -o game 

