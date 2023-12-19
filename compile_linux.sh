

#clang++ main.cpp -Wall -o3 -o ./bin/game -Ilibs/SDL2-linux/include -Llibs/SDL2-linux/lib -lSDL2 -lSDL2main

#g++ main.cpp -Wall -o3 -o ./bin/game -Ilibs/SDL2-linux/include -Llibs/SDL2-linux/lib -lSDL2 -lSDL2main

#g++ main.cpp shader.cpp material.cpp mesh.cpp mesh_instance.cpp mesh_utils.cpp texture.cpp camera.cpp application.cpp scene.cpp game_scene.cpp object_2d.cpp tile_map.cpp sprite.cpp \
#    -g -Wall -o3 -o ./bin/game $(pkg-config --cflags --libs sdl2 glew)

#g++ -Wall -fexceptions -I/usr/include/SDL2 -D_REENTRANT -g -Isfw -c sfw/aabb.cpp -o sfw/aabb.o

# g++ -Wall -D_REENTRANT -g -Isfw -c sfw/aabb.cpp -o sfw/aabb.o
# g++ -Wall -D_REENTRANT -g -Isfw -c sfw/basis.cpp -o sfw/basis.o
# g++ -Wall -D_REENTRANT -g -Isfw -c sfw/color.cpp -o sfw/color.o
# g++ -Wall -D_REENTRANT -g -Isfw -c sfw/face3.cpp -o sfw/face3.o
# g++ -Wall -D_REENTRANT -g -Isfw -c sfw/logger.cpp -o sfw/logger.o
# g++ -Wall -D_REENTRANT -g -Isfw -c sfw/math_funcs.cpp -o sfw/math_funcs.o
# g++ -Wall -D_REENTRANT -g -Isfw -c sfw/memory.cpp -o sfw/memory.o
# g++ -Wall -D_REENTRANT -g -Isfw -c sfw/pcg.cpp -o sfw/pcg.o
# g++ -Wall -D_REENTRANT -g -Isfw -c sfw/plane.cpp -o sfw/plane.o
# g++ -Wall -D_REENTRANT -g -Isfw -c sfw/projection.cpp -o sfw/projection.o
# g++ -Wall -D_REENTRANT -g -Isfw -c sfw/quaternion.cpp -o sfw/quaternion.o
# g++ -Wall -D_REENTRANT -g -Isfw -c sfw/random_pcg.cpp -o sfw/random_pcg.o
# g++ -Wall -D_REENTRANT -g -Isfw -c sfw/rect2.cpp -o sfw/rect2.o
# g++ -Wall -D_REENTRANT -g -Isfw -c sfw/rect2i.cpp -o sfw/rect2i.o
# g++ -Wall -D_REENTRANT -g -Isfw -c sfw/safe_refcount.cpp -o sfw/safe_refcount.o
# g++ -Wall -D_REENTRANT -g -Isfw -c sfw/transform_2d.cpp -o sfw/transform_2d.o
# g++ -Wall -D_REENTRANT -g -Isfw -c sfw/transform.cpp -o sfw/transform.o
# g++ -Wall -D_REENTRANT -g -Isfw -c sfw/ustring.cpp -o sfw/ustring.o
# g++ -Wall -D_REENTRANT -g -Isfw -c sfw/vector2.cpp -o sfw/vector2.o
# g++ -Wall -D_REENTRANT -g -Isfw -c sfw/vector2i.cpp -o sfw/vector2i.o
# g++ -Wall -D_REENTRANT -g -Isfw -c sfw/vector3.cpp -o sfw/vector3.o
# g++ -Wall -D_REENTRANT -g -Isfw -c sfw/vector3i.cpp -o sfw/vector3i.o
# g++ -Wall -D_REENTRANT -g -Isfw -c sfw/vector4.cpp -o sfw/vector4.o
# g++ -Wall -D_REENTRANT -g -Isfw -c sfw/vector4i.cpp -o sfw/vector4i.o

# g++ -Wall -D_REENTRANT -g -Isfw -c sfw/pool_vector.cpp -o sfw/pool_vector.o
# g++ -Wall -D_REENTRANT -g -Isfw -c sfw/pool_allocator.cpp -o sfw/pool_allocator.o
# g++ -Wall -D_REENTRANT -g -Isfw -c sfw/mutex.cpp -o sfw/mutex.o
#g++ -Wall -D_REENTRANT -g -Isfw -c sfw/stime.cpp -o sfw/stime.o

#g++ -Wall -D_REENTRANT -g -Isfw -Isfw/application -c sfw/application/application.cpp -o sfw/application/application.o
#g++ -Wall -D_REENTRANT -g -Isfw -Isfw/application -c sfw/application/scene.cpp -o sfw/application/scene.o
g++ -Wall -D_REENTRANT -g -Isfw -Isfw/application -c sfw/application/window.cpp -o sfw/application/window.o
