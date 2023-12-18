

#clang++ main.cpp -Wall -o3 -o ./bin/game -Ilibs/SDL2-linux/include -Llibs/SDL2-linux/lib -lSDL2 -lSDL2main

#g++ main.cpp -Wall -o3 -o ./bin/game -Ilibs/SDL2-linux/include -Llibs/SDL2-linux/lib -lSDL2 -lSDL2main

g++ main.cpp -Wall -o3 -o ./game $(pkg-config --cflags --libs sdl2 glew)