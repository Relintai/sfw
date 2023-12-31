

#clang++ main.cpp -Wall -o3 -o ./bin/game -Ilibs/SDL2-linux/include -Llibs/SDL2-linux/lib -lSDL2 -lSDL2main

#g++ main.cpp -Wall -o3 -o ./bin/game -Ilibs/SDL2-linux/include -Llibs/SDL2-linux/lib -lSDL2 -lSDL2main

#g++ main.cpp shader.cpp material.cpp mesh.cpp mesh_instance.cpp mesh_utils.cpp texture.cpp camera.cpp render_core.cpp scene.cpp game_scene.cpp object_2d.cpp tile_map.cpp sprite.cpp \
#    -g -Wall -o3 -o ./bin/game $(pkg-config --cflags --libs sdl2 glew)

#g++ -Wall -fexceptions -I/usr/include/SDL2 -D_REENTRANT -g -Isfw -c sfw/core/aabb.cpp -o sfw/core/aabb.o

ccache g++ -Wall -D_REENTRANT -g -Isfw -c sfw/core/aabb.cpp -o sfw/core/aabb.o
ccache g++ -Wall -D_REENTRANT -g -Isfw -c sfw/core/basis.cpp -o sfw/core/basis.o
ccache g++ -Wall -D_REENTRANT -g -Isfw -c sfw/core/color.cpp -o sfw/core/color.o
ccache g++ -Wall -D_REENTRANT -g -Isfw -c sfw/core/face3.cpp -o sfw/core/face3.o
ccache g++ -Wall -D_REENTRANT -g -Isfw -c sfw/core/logger.cpp -o sfw/core/logger.o
ccache g++ -Wall -D_REENTRANT -g -Isfw -c sfw/core/math_funcs.cpp -o sfw/core/math_funcs.o
ccache g++ -Wall -D_REENTRANT -g -Isfw -c sfw/core/memory.cpp -o sfw/core/memory.o
ccache g++ -Wall -D_REENTRANT -g -Isfw -c sfw/core/pcg.cpp -o sfw/core/pcg.o
ccache g++ -Wall -D_REENTRANT -g -Isfw -c sfw/core/plane.cpp -o sfw/core/plane.o
ccache g++ -Wall -D_REENTRANT -g -Isfw -c sfw/core/projection.cpp -o sfw/core/projection.o
ccache g++ -Wall -D_REENTRANT -g -Isfw -c sfw/core/quaternion.cpp -o sfw/core/quaternion.o
ccache g++ -Wall -D_REENTRANT -g -Isfw -c sfw/core/random_pcg.cpp -o sfw/core/random_pcg.o
ccache g++ -Wall -D_REENTRANT -g -Isfw -c sfw/core/rect2.cpp -o sfw/core/rect2.o
ccache g++ -Wall -D_REENTRANT -g -Isfw -c sfw/core/rect2i.cpp -o sfw/core/rect2i.o
ccache g++ -Wall -D_REENTRANT -g -Isfw -c sfw/core/safe_refcount.cpp -o sfw/core/safe_refcount.o
ccache g++ -Wall -D_REENTRANT -g -Isfw -c sfw/core/transform_2d.cpp -o sfw/core/transform_2d.o
ccache g++ -Wall -D_REENTRANT -g -Isfw -c sfw/core/transform.cpp -o sfw/core/transform.o
ccache g++ -Wall -D_REENTRANT -g -Isfw -c sfw/core/ustring.cpp -o sfw/core/ustring.o
ccache g++ -Wall -D_REENTRANT -g -Isfw -c sfw/core/string_name.cpp -o sfw/core/string_name.o
ccache g++ -Wall -D_REENTRANT -g -Isfw -c sfw/core/vector2.cpp -o sfw/core/vector2.o
ccache g++ -Wall -D_REENTRANT -g -Isfw -c sfw/core/vector2i.cpp -o sfw/core/vector2i.o
ccache g++ -Wall -D_REENTRANT -g -Isfw -c sfw/core/vector3.cpp -o sfw/core/vector3.o
ccache g++ -Wall -D_REENTRANT -g -Isfw -c sfw/core/vector3i.cpp -o sfw/core/vector3i.o
ccache g++ -Wall -D_REENTRANT -g -Isfw -c sfw/core/vector4.cpp -o sfw/core/vector4.o
ccache g++ -Wall -D_REENTRANT -g -Isfw -c sfw/core/vector4i.cpp -o sfw/core/vector4i.o

ccache g++ -Wall -D_REENTRANT -g -Isfw -c sfw/core/pool_vector.cpp -o sfw/core/pool_vector.o
ccache g++ -Wall -D_REENTRANT -g -Isfw -c sfw/core/pool_allocator.cpp -o sfw/core/pool_allocator.o
ccache g++ -Wall -D_REENTRANT -g -Isfw -c sfw/core/mutex.cpp -o sfw/core/mutex.o
ccache g++ -Wall -D_REENTRANT -g -Isfw -c sfw/core/stime.cpp -o sfw/core/stime.o

ccache g++ -Wall -D_REENTRANT -g -Isfw -c sfw/object/object.cpp -o sfw/object/object.o
ccache g++ -Wall -D_REENTRANT -g -Isfw -c sfw/object/reference.cpp -o sfw/object/reference.o
ccache g++ -Wall -D_REENTRANT -g -Isfw -c sfw/object/core_string_names.cpp -o sfw/object/core_string_names.o
ccache g++ -Wall -D_REENTRANT -g -Isfw -c sfw/object/variant.cpp -o sfw/object/variant.o
ccache g++ -Wall -D_REENTRANT -g -Isfw -c sfw/object/variant_op.cpp -o sfw/object/variant_op.o
ccache g++ -Wall -D_REENTRANT -g -Isfw -c sfw/object/psignal.cpp -o sfw/object/psignal.o
ccache g++ -Wall -D_REENTRANT -g -Isfw -c sfw/object/array.cpp -o sfw/object/array.o
ccache g++ -Wall -D_REENTRANT -g -Isfw -c sfw/object/dictionary.cpp -o sfw/object/dictionary.o
ccache g++ -Wall -D_REENTRANT -g -Isfw -c sfw/object/ref_ptr.cpp -o sfw/object/ref_ptr.o

ccache g++ -Wall -D_REENTRANT -g -Isfw -c sfw/render_core/application.cpp -o sfw/render_core/application.o
ccache g++ -Wall -D_REENTRANT -g -Isfw -c sfw/render_core/scene.cpp -o sfw/render_core/scene.o
ccache g++ -Wall -D_REENTRANT -g -Isfw -c sfw/render_core/window.cpp -o sfw/render_core/window.o

ccache g++ -Wall -D_REENTRANT -g -Isfw -c sfw/render_core/shader.cpp -o sfw/render_core/shader.o
ccache g++ -Wall -D_REENTRANT -g -Isfw -c sfw/render_core/material.cpp -o sfw/render_core/material.o
ccache g++ -Wall -D_REENTRANT -g -Isfw -c sfw/render_core/mesh.cpp -o sfw/render_core/mesh.o
ccache g++ -Wall -D_REENTRANT -g -Isfw -c sfw/render_core/mesh_utils.cpp -o sfw/render_core/mesh_utils.o
ccache g++ -Wall -D_REENTRANT -g -Isfw -c sfw/render_core/texture.cpp -o sfw/render_core/texture.o
ccache g++ -Wall -D_REENTRANT -g -Isfw -c sfw/render_core/image.cpp -o sfw/render_core/image.o

ccache g++ -Wall -D_REENTRANT -g -Isfw -c sfw/render_objects/camera_3d.cpp -o sfw/render_objects/camera_3d.o
ccache g++ -Wall -D_REENTRANT -g -Isfw -c sfw/render_objects/object_3d.cpp -o sfw/render_objects/object_3d.o
ccache g++ -Wall -D_REENTRANT -g -Isfw -c sfw/render_objects/mesh_instance_3d.cpp -o sfw/render_objects/mesh_instance_3d.o

ccache g++ -Wall -D_REENTRANT -g -Isfw -c sfw/render_objects/camera_2d.cpp -o sfw/render_objects/camera_2d.o
ccache g++ -Wall -D_REENTRANT -g -Isfw -c sfw/render_objects/mesh_instance_2d.cpp -o sfw/render_objects/mesh_instance_2d.o
ccache g++ -Wall -D_REENTRANT -g -Isfw -c sfw/render_objects/object_2d.cpp -o sfw/render_objects/object_2d.o
ccache g++ -Wall -D_REENTRANT -g -Isfw -c sfw/render_objects/sprite.cpp -o sfw/render_objects/sprite.o
ccache g++ -Wall -D_REENTRANT -g -Isfw -c sfw/render_objects/tile_map.cpp -o sfw/render_objects/tile_map.o

ccache g++ -Wall -D_REENTRANT -g -Isfw -c game_scene.cpp -o game_scene.o
ccache g++ -Wall -D_REENTRANT -g -Isfw -c main.cpp -o main.o


ccache g++ -Wall -lm -ldl -lpthread -lX11  -D_REENTRANT -g sfw/core/aabb.o sfw/core/basis.o sfw/core/color.o \
                        sfw/core/face3.o sfw/core/logger.o sfw/core/math_funcs.o \
                        sfw/core/memory.o sfw/core/pcg.o sfw/core/plane.o sfw/core/projection.o sfw/core/quaternion.o sfw/core/random_pcg.o \
                        sfw/core/rect2.o sfw/core/rect2i.o sfw/core/safe_refcount.o sfw/core/transform_2d.o sfw/core/transform.o \
                        sfw/core/ustring.o sfw/core/string_name.o \
                        sfw/core/vector2.o sfw/core/vector2i.o sfw/core/vector3.o \
                        sfw/core/vector3i.o sfw/core/vector4.o sfw/core/vector4i.o \
                        sfw/core/pool_vector.o sfw/core/pool_allocator.o sfw/core/mutex.o sfw/core/stime.o \
                        sfw/object/object.o sfw/object/reference.o sfw/object/core_string_names.o \
                        sfw/object/variant.o sfw/object/variant_op.o sfw/object/psignal.o \
                        sfw/object/array.o sfw/object/dictionary.o sfw/object/ref_ptr.o \
                        sfw/render_core/image.o \
                        sfw/render_core/application.o sfw/render_core/scene.o sfw/render_core/window.o \
                        sfw/render_core/shader.o sfw/render_core/material.o sfw/render_core/mesh.o \
                        sfw/render_core/mesh_utils.o sfw/render_core/texture.o \
                        sfw/render_objects/camera_3d.o sfw/render_objects/object_3d.o sfw/render_objects/mesh_instance_3d.o \
                        sfw/render_objects/object_2d.o \
                        sfw/render_objects/sprite.o sfw/render_objects/tile_map.o \
                        sfw/render_objects/camera_2d.o sfw/render_objects/mesh_instance_2d.o \
                        game_scene.o main.o \
                         -o game 


#export args="-lm -ldl -lpthread -lX11 -w -Iengine/ $args"