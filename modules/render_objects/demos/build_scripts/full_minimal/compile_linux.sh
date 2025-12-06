
g++ -Wall -g -c sfw.cpp -o sfw.o
g++ -Wall -g -c sfw_render_objects.cpp -o sfw_render_objects.o
g++ -Wall -g -c main.cpp -o main.o

g++ -Wall -static-libgcc -static-libstdc++ -g sfw.o sfw_render_objects.o main.o -lX11 -o game 
