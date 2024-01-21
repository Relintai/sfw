cp -u ../tools/merger/out/full/sfw.h sfw.h
cp -u ../tools/merger/out/full/sfw.cpp sfw.cpp
cp -u ../tools/merger/out/full/sfw_3rd.m sfw_3rd.m

ccache g++ -Wall -g -c sfw.cpp -o sfw.o
ccache g++ -Wall -g -c game_scene.cpp -o game_scene.o
ccache g++ -Wall -g -c main.cpp -o main.o

ccache g++ -Wall -lX11 -static-libgcc -static-libstdc++ -g sfw.o game_scene.o main.o -o game 
