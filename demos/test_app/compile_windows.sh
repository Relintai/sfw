cp -u ../out/full/sfw.h sfw.h
cp -u ../out/full/sfw.cpp sfw.cpp
cp -u ../out/full/sfw_3rd.m sfw_3rd.m

ccache g++ -Wall -g -c sfw.cpp -o sfw.o
ccache g++ -Wall -g -c game_scene.cpp -o game_scene.o
ccache g++ -Wall -g -c main.cpp -o main.o

# You might need to add -lpthread and/or -latomic depending on your compiler version

ccache g++ -Wall -g sfw.o game_scene.o main.o \
                        -lgdi32 -lShlwapi -lws2_32 \
                        -o game 
