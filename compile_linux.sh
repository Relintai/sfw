

#clang++ main.cpp -Wall -o3 -o ./bin/game -Ilibs/SDL2-linux/include -Llibs/SDL2-linux/lib -lSDL2 -lSDL2main

#g++ main.cpp -Wall -o3 -o ./bin/game -Ilibs/SDL2-linux/include -Llibs/SDL2-linux/lib -lSDL2 -lSDL2main

#g++ main.cpp shader.cpp material.cpp mesh.cpp mesh_instance.cpp mesh_utils.cpp texture.cpp camera.cpp application.cpp scene.cpp game_scene.cpp object_2d.cpp tile_map.cpp sprite.cpp \
#    -g -Wall -o3 -o ./bin/game $(pkg-config --cflags --libs sdl2 glew)

#g++ -Wall -fexceptions -I/usr/include/SDL2 -D_REENTRANT -g -Isfw -c sfw/aabb.cpp -o sfw/aabb.o

ccache g++ -Wall -D_REENTRANT -g -Isfw -c sfw/aabb.cpp -o sfw/aabb.o
ccache g++ -Wall -D_REENTRANT -g -Isfw -c sfw/basis.cpp -o sfw/basis.o
ccache g++ -Wall -D_REENTRANT -g -Isfw -c sfw/color.cpp -o sfw/color.o
ccache g++ -Wall -D_REENTRANT -g -Isfw -c sfw/face3.cpp -o sfw/face3.o
ccache g++ -Wall -D_REENTRANT -g -Isfw -c sfw/logger.cpp -o sfw/logger.o
ccache g++ -Wall -D_REENTRANT -g -Isfw -c sfw/math_funcs.cpp -o sfw/math_funcs.o
ccache g++ -Wall -D_REENTRANT -g -Isfw -c sfw/memory.cpp -o sfw/memory.o
ccache g++ -Wall -D_REENTRANT -g -Isfw -c sfw/pcg.cpp -o sfw/pcg.o
ccache g++ -Wall -D_REENTRANT -g -Isfw -c sfw/plane.cpp -o sfw/plane.o
ccache g++ -Wall -D_REENTRANT -g -Isfw -c sfw/projection.cpp -o sfw/projection.o
ccache g++ -Wall -D_REENTRANT -g -Isfw -c sfw/quaternion.cpp -o sfw/quaternion.o
ccache g++ -Wall -D_REENTRANT -g -Isfw -c sfw/random_pcg.cpp -o sfw/random_pcg.o
ccache g++ -Wall -D_REENTRANT -g -Isfw -c sfw/rect2.cpp -o sfw/rect2.o
ccache g++ -Wall -D_REENTRANT -g -Isfw -c sfw/rect2i.cpp -o sfw/rect2i.o
ccache g++ -Wall -D_REENTRANT -g -Isfw -c sfw/safe_refcount.cpp -o sfw/safe_refcount.o
ccache g++ -Wall -D_REENTRANT -g -Isfw -c sfw/transform_2d.cpp -o sfw/transform_2d.o
ccache g++ -Wall -D_REENTRANT -g -Isfw -c sfw/transform.cpp -o sfw/transform.o
ccache g++ -Wall -D_REENTRANT -g -Isfw -c sfw/ustring.cpp -o sfw/ustring.o
ccache g++ -Wall -D_REENTRANT -g -Isfw -c sfw/vector2.cpp -o sfw/vector2.o
ccache g++ -Wall -D_REENTRANT -g -Isfw -c sfw/vector2i.cpp -o sfw/vector2i.o
ccache g++ -Wall -D_REENTRANT -g -Isfw -c sfw/vector3.cpp -o sfw/vector3.o
ccache g++ -Wall -D_REENTRANT -g -Isfw -c sfw/vector3i.cpp -o sfw/vector3i.o
ccache g++ -Wall -D_REENTRANT -g -Isfw -c sfw/vector4.cpp -o sfw/vector4.o
ccache g++ -Wall -D_REENTRANT -g -Isfw -c sfw/vector4i.cpp -o sfw/vector4i.o

ccache g++ -Wall -D_REENTRANT -g -Isfw -c sfw/pool_vector.cpp -o sfw/pool_vector.o
ccache g++ -Wall -D_REENTRANT -g -Isfw -c sfw/pool_allocator.cpp -o sfw/pool_allocator.o
ccache g++ -Wall -D_REENTRANT -g -Isfw -c sfw/mutex.cpp -o sfw/mutex.o
ccache g++ -Wall -D_REENTRANT -g -Isfw -c sfw/stime.cpp -o sfw/stime.o

ccache g++ -Wall -D_REENTRANT -g -Isfw -Isfw/application -c sfw/application/application.cpp -o sfw/application/application.o
ccache g++ -Wall -D_REENTRANT -g -Isfw -Isfw/application -c sfw/application/scene.cpp -o sfw/application/scene.o
ccache g++ -Wall -D_REENTRANT -g -Isfw -Isfw/application -c sfw/application/window.cpp -o sfw/application/window.o


ccache g++ -Wall -D_REENTRANT -g -Isfw -Isfw/application -c sfw/application/shader.cpp -o sfw/application/shader.o
ccache g++ -Wall -D_REENTRANT -g -Isfw -Isfw/application -c sfw/application/material.cpp -o sfw/application/material.o
ccache g++ -Wall -D_REENTRANT -g -Isfw -Isfw/application -c sfw/application/mesh.cpp -o sfw/application/mesh.o
ccache g++ -Wall -D_REENTRANT -g -Isfw -Isfw/application -c sfw/application/camera.cpp -o sfw/application/camera.o
ccache g++ -Wall -D_REENTRANT -g -Isfw -Isfw/application -c sfw/application/mesh_instance.cpp -o sfw/application/mesh_instance.o
ccache g++ -Wall -D_REENTRANT -g -Isfw -Isfw/application -c sfw/application/object_2d.cpp -o sfw/application/object_2d.o
ccache g++ -Wall -D_REENTRANT -g -Isfw -Isfw/application -c sfw/application/sprite.cpp -o sfw/application/sprite.o
ccache g++ -Wall -D_REENTRANT -g -Isfw -Isfw/application -c sfw/application/tile_map.cpp -o sfw/application/tile_map.o
ccache g++ -Wall -D_REENTRANT -g -Isfw -Isfw/application -c sfw/application/texture.cpp -o sfw/application/texture.o

ccache g++ -Wall -D_REENTRANT -g -Isfw -Isfw/application -c game_scene.cpp -o game_scene.o
ccache g++ -Wall -D_REENTRANT -g -Isfw -Isfw/application -c main.cpp -o main.o


ccache g++ -Wall -lm -ldl -lpthread -lX11  -D_REENTRANT -g sfw/aabb.o sfw/basis.o sfw/color.o sfw/face3.o sfw/logger.o sfw/math_funcs.o \
                        sfw/memory.o sfw/pcg.o sfw/plane.o sfw/projection.o sfw/quaternion.o sfw/random_pcg.o \
                        sfw/rect2.o sfw/rect2i.o sfw/safe_refcount.o sfw/transform_2d.o sfw/transform.o \
                        sfw/ustring.o sfw/vector2.o sfw/vector2i.o sfw/vector3.o sfw/vector3i.o sfw/vector4.o sfw/vector4i.o \
                        sfw/pool_vector.o sfw/pool_allocator.o sfw/mutex.o sfw/stime.o \
                        sfw/application/application.o sfw/application/scene.o sfw/application/window.o \
                        sfw/application/shader.o sfw/application/material.o sfw/application/mesh.o \
                        sfw/application/camera.o sfw/application/mesh_instance.o sfw/application/object_2d.o \
                        sfw/application/sprite.o sfw/application/tile_map.o sfw/application/texture.o \
                        game_scene.o main.o \
                         -o game 


#export args="-lm -ldl -lpthread -lX11 -w -Iengine/ $args"