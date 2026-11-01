

#clang++ main.cpp -Wall -o3 -o ./bin/game -Ilibs/SDL2-linux/include -Llibs/SDL2-linux/lib -lSDL2 -lSDL2main

#g++ main.cpp -Wall -o3 -o ./bin/game -Ilibs/SDL2-linux/include -Llibs/SDL2-linux/lib -lSDL2 -lSDL2main

#g++ main.cpp shader.cpp material.cpp mesh.cpp mesh_instance.cpp mesh_utils.cpp texture.cpp camera.cpp render_core.cpp scene.cpp game_scene.cpp object_2d.cpp tile_map.cpp sprite.cpp \
#    -g -Wall -o3 -o ./bin/game $(pkg-config --cflags --libs sdl2 glew)

#g++ -Wall -fexceptions -I/usr/include/SDL2 -D_REENTRANT -g -Isfw -c sfw/core/aabb.cpp -o sfw/core/aabb.o

export SDKROOT=$(xcrun --show-sdk-path)

export args="-std=c++14 -w -framework cocoa -framework iokit -framework CoreFoundation -framework CoreAudio -framework AudioToolbox "

clang++ $args -D_REENTRANT -g -Isfw -c sfw/core/aabb.cpp -o sfw/core/aabb.o
clang++ $args -D_REENTRANT -g -Isfw -c sfw/core/basis.cpp -o sfw/core/basis.o
clang++ $args -D_REENTRANT -g -Isfw -c sfw/core/color.cpp -o sfw/core/color.o
clang++ $args -D_REENTRANT -g -Isfw -c sfw/core/face3.cpp -o sfw/core/face3.o
clang++ $args -D_REENTRANT -g -Isfw -c sfw/core/logger.cpp -o sfw/core/logger.o
clang++ $args -D_REENTRANT -g -Isfw -c sfw/core/math_funcs.cpp -o sfw/core/math_funcs.o
clang++ $args -D_REENTRANT -g -Isfw -c sfw/core/memory.cpp -o sfw/core/memory.o
clang++ $args -D_REENTRANT -g -Isfw -c sfw/core/pcg.cpp -o sfw/core/pcg.o
clang++ $args -D_REENTRANT -g -Isfw -c sfw/core/plane.cpp -o sfw/core/plane.o
clang++ $args -D_REENTRANT -g -Isfw -c sfw/core/projection.cpp -o sfw/core/projection.o
clang++ $args -D_REENTRANT -g -Isfw -c sfw/core/quaternion.cpp -o sfw/core/quaternion.o
clang++ $args -D_REENTRANT -g -Isfw -c sfw/core/random_pcg.cpp -o sfw/core/random_pcg.o
clang++ $args -D_REENTRANT -g -Isfw -c sfw/core/rect2.cpp -o sfw/core/rect2.o
clang++ $args -D_REENTRANT -g -Isfw -c sfw/core/rect2i.cpp -o sfw/core/rect2i.o
clang++ $args -D_REENTRANT -g -Isfw -c sfw/core/safe_refcount.cpp -o sfw/core/safe_refcount.o
clang++ $args -D_REENTRANT -g -Isfw -c sfw/core/transform_2d.cpp -o sfw/core/transform_2d.o
clang++ $args -D_REENTRANT -g -Isfw -c sfw/core/transform.cpp -o sfw/core/transform.o
clang++ $args -D_REENTRANT -g -Isfw -c sfw/core/ustring.cpp -o sfw/core/ustring.o
clang++ $args -D_REENTRANT -g -Isfw -c sfw/core/string_name.cpp -o sfw/core/string_name.o
clang++ $args -D_REENTRANT -g -Isfw -c sfw/core/vector2.cpp -o sfw/core/vector2.o
clang++ $args -D_REENTRANT -g -Isfw -c sfw/core/vector2i.cpp -o sfw/core/vector2i.o
clang++ $args -D_REENTRANT -g -Isfw -c sfw/core/vector3.cpp -o sfw/core/vector3.o
clang++ $args -D_REENTRANT -g -Isfw -c sfw/core/vector3i.cpp -o sfw/core/vector3i.o
clang++ $args -D_REENTRANT -g -Isfw -c sfw/core/vector4.cpp -o sfw/core/vector4.o
clang++ $args -D_REENTRANT -g -Isfw -c sfw/core/vector4i.cpp -o sfw/core/vector4i.o

clang++ $args -D_REENTRANT -g -Isfw -c sfw/core/file_access.cpp -o sfw/core/file_access.o
clang++ $args -D_REENTRANT -g -Isfw -c sfw/core/dir_access.cpp -o sfw/core/dir_access.o

clang++ $args -D_REENTRANT -g -Isfw -c sfw/core/pool_vector.cpp -o sfw/core/pool_vector.o
clang++ $args -D_REENTRANT -g -Isfw -c sfw/core/pool_allocator.cpp -o sfw/core/pool_allocator.o
clang++ $args -D_REENTRANT -g -Isfw -c sfw/core/mutex.cpp -o sfw/core/mutex.o
clang++ $args -D_REENTRANT -g -Isfw -c sfw/core/rw_lock.cpp -o sfw/core/rw_lock.o
clang++ $args -D_REENTRANT -g -Isfw -c sfw/core/semaphore.cpp -o sfw/core/semaphore.o
clang++ $args -D_REENTRANT -g -Isfw -c sfw/core/sfw_time.cpp -o sfw/core/sfw_time.o
clang++ $args -D_REENTRANT -g -Isfw -c sfw/core/string_builder.cpp -o sfw/core/string_builder.o

clang++ $args -D_REENTRANT -g -Isfw -c sfw/core/thread.cpp -o sfw/core/thread.o
clang++ $args -D_REENTRANT -g -Isfw -c sfw/core/socket.cpp -o sfw/core/socket.o
clang++ $args -D_REENTRANT -g -Isfw -c sfw/core/inet_address.cpp -o sfw/core/inet_address.o

clang++ $args -D_REENTRANT -g -Isfw -c sfw/core/sub_process.cpp -o sfw/core/sub_process.o

clang++ $args -D_REENTRANT -g -Isfw -c sfw/core/sfw_core.cpp -o sfw/core/sfw_core.o

clang++ $args -D_REENTRANT -g -Isfw -c sfw/core/os.cpp -o sfw/core/os.o

clang++ $args -D_REENTRANT -g -Isfw -c sfw/object/object.cpp -o sfw/object/object.o
clang++ $args -D_REENTRANT -g -Isfw -c sfw/object/reference.cpp -o sfw/object/reference.o
clang++ $args -D_REENTRANT -g -Isfw -c sfw/object/core_string_names.cpp -o sfw/object/core_string_names.o
clang++ $args -D_REENTRANT -g -Isfw -c sfw/object/variant.cpp -o sfw/object/variant.o
clang++ $args -D_REENTRANT -g -Isfw -c sfw/object/variant_op.cpp -o sfw/object/variant_op.o
clang++ $args -D_REENTRANT -g -Isfw -c sfw/object/psignal.cpp -o sfw/object/psignal.o
clang++ $args -D_REENTRANT -g -Isfw -c sfw/object/array.cpp -o sfw/object/array.o
clang++ $args -D_REENTRANT -g -Isfw -c sfw/object/dictionary.cpp -o sfw/object/dictionary.o
clang++ $args -D_REENTRANT -g -Isfw -c sfw/object/ref_ptr.cpp -o sfw/object/ref_ptr.o
clang++ $args -D_REENTRANT -g -Isfw -c sfw/object/resource.cpp -o sfw/object/resource.o

clang++ $args -D_REENTRANT -g -Isfw -c sfw/render_core/application.cpp -o sfw/render_core/application.o
clang++ $args -D_REENTRANT -g -Isfw -c sfw/render_core/scene.cpp -o sfw/render_core/scene.o
clang++ $args -D_REENTRANT -g -Isfw -c sfw/render_core/app_window.cpp -o sfw/render_core/app_window.o

clang++ $args -D_REENTRANT -g -Isfw -c sfw/render_core/shader.cpp -o sfw/render_core/shader.o
clang++ $args -D_REENTRANT -g -Isfw -c sfw/render_core/material.cpp -o sfw/render_core/material.o
clang++ $args -D_REENTRANT -g -Isfw -c sfw/render_core/mesh.cpp -o sfw/render_core/mesh.o
clang++ $args -D_REENTRANT -g -Isfw -c sfw/render_core/mesh_utils.cpp -o sfw/render_core/mesh_utils.o
clang++ $args -D_REENTRANT -g -Isfw -c sfw/render_core/texture.cpp -o sfw/render_core/texture.o
clang++ $args -D_REENTRANT -g -Isfw -c sfw/render_core/frame_buffer.cpp -o sfw/render_core/frame_buffer.o
clang++ $args -D_REENTRANT -g -Isfw -c sfw/render_core/image.cpp -o sfw/render_core/image.o
clang++ $args -D_REENTRANT -g -Isfw -c sfw/render_core/render_state.cpp -o sfw/render_core/render_state.o
clang++ $args -D_REENTRANT -g -Isfw -c sfw/render_core/keyboard.cpp -o sfw/render_core/keyboard.o
clang++ $args -D_REENTRANT -g -Isfw -c sfw/render_core/input_event.cpp -o sfw/render_core/input_event.o
clang++ $args -D_REENTRANT -g -Isfw -c sfw/render_core/input_map.cpp -o sfw/render_core/input_map.o
clang++ $args -D_REENTRANT -g -Isfw -c sfw/render_core/input.cpp -o sfw/render_core/input.o
clang++ $args -D_REENTRANT -g -Isfw -c sfw/render_core/shortcut.cpp -o sfw/render_core/shortcut.o
clang++ $args -D_REENTRANT -g -Isfw -c sfw/render_core/font.cpp -o sfw/render_core/font.o

clang++ $args -D_REENTRANT -g -Isfw -c sfw/render_core/color_material_2d.cpp -o sfw/render_core/color_material_2d.o
clang++ $args -D_REENTRANT -g -Isfw -c sfw/render_core/color_material.cpp -o sfw/render_core/color_material.o
clang++ $args -D_REENTRANT -g -Isfw -c sfw/render_core/colored_material.cpp -o sfw/render_core/colored_material.o
clang++ $args -D_REENTRANT -g -Isfw -c sfw/render_core/font_material.cpp -o sfw/render_core/font_material.o
clang++ $args -D_REENTRANT -g -Isfw -c sfw/render_core/texture_material_2d.cpp -o sfw/render_core/texture_material_2d.o
clang++ $args -D_REENTRANT -g -Isfw -c sfw/render_core/texture_material.cpp -o sfw/render_core/texture_material.o
clang++ $args -D_REENTRANT -g -Isfw -c sfw/render_core/transparent_texture_material.cpp -o sfw/render_core/transparent_texture_material.o
clang++ $args -D_REENTRANT -g -Isfw -c sfw/render_core/colored_texture_material_2d.cpp -o sfw/render_core/colored_texture_material_2d.o

clang++ -w -framework cocoa -framework iokit -framework CoreFoundation -framework CoreAudio -framework AudioToolbox -D_REENTRANT -g -Isfw -c sfw/render_core/glfw_impl.m -o sfw/render_core/glfw_impl.o

clang++ $args -D_REENTRANT -g -Isfw -c sfw/render_immediate/renderer.cpp -o sfw/render_immediate/renderer.o

clang++ $args -D_REENTRANT -g -Isfw -c sfw/render_gui/imgui.cpp -o sfw/render_gui/imgui.o
clang++ $args -D_REENTRANT -g -Isfw -c sfw/render_gui/imgui_draw.cpp -o sfw/render_gui/imgui_draw.o
clang++ $args -D_REENTRANT -g -Isfw -c sfw/render_gui/imgui_impl_glfw.cpp -o sfw/render_gui/imgui_impl_glfw.o
clang++ $args -D_REENTRANT -g -Isfw -c sfw/render_gui/imgui_impl_opengl3.cpp -o sfw/render_gui/imgui_impl_opengl3.o
clang++ $args -D_REENTRANT -g -Isfw -c sfw/render_gui/imgui_tables.cpp -o sfw/render_gui/imgui_tables.o
clang++ $args -D_REENTRANT -g -Isfw -c sfw/render_gui/imgui_widgets.cpp -o sfw/render_gui/imgui_widgets.o
clang++ $args -D_REENTRANT -g -Isfw -c sfw/render_gui/gui.cpp -o sfw/render_gui/gui.o

clang++ $args -D_REENTRANT -g -Isfw -c sfw/game_scene.cpp -o sfw/game_scene.o
clang++ $args -D_REENTRANT -g -Isfw -c sfw/main.cpp -o sfw/main.o

# You might need to add -lpthread and/or -latomic depending on your compiler version

clang++ $args -D_REENTRANT -g sfw/core/aabb.o sfw/core/basis.o sfw/core/color.o \
                        sfw/core/face3.o sfw/core/logger.o sfw/core/math_funcs.o \
                        sfw/core/memory.o sfw/core/pcg.o sfw/core/plane.o sfw/core/projection.o sfw/core/quaternion.o sfw/core/random_pcg.o \
                        sfw/core/rect2.o sfw/core/rect2i.o sfw/core/safe_refcount.o sfw/core/transform_2d.o sfw/core/transform.o \
                        sfw/core/ustring.o sfw/core/string_name.o \
                        sfw/core/rw_lock.o sfw/core/semaphore.o \
                        sfw/core/vector2.o sfw/core/vector2i.o sfw/core/vector3.o \
                        sfw/core/vector3i.o sfw/core/vector4.o sfw/core/vector4i.o \
                        sfw/core/pool_vector.o sfw/core/pool_allocator.o sfw/core/mutex.o sfw/core/sfw_time.o \
												sfw/core/string_builder.o \
                        sfw/core/dir_access.o sfw/core/file_access.o sfw/core/thread.o \
                        sfw/core/socket.o sfw/core/inet_address.o \
                        sfw/core/sub_process.o \
                        sfw/core/sfw_core.o \
                        sfw/core/os.o \
                        sfw/object/object.o sfw/object/reference.o sfw/object/core_string_names.o \
                        sfw/object/variant.o sfw/object/variant_op.o sfw/object/psignal.o \
                        sfw/object/array.o sfw/object/dictionary.o sfw/object/ref_ptr.o \
                        sfw/object/resource.o \
                        sfw/render_core/image.o sfw/render_core/render_state.o \
                        sfw/render_core/application.o sfw/render_core/scene.o sfw/render_core/app_window.o \
                        sfw/render_core/shader.o sfw/render_core/material.o sfw/render_core/mesh.o \
                        sfw/render_core/mesh_utils.o sfw/render_core/texture.o \
                        sfw/render_core/frame_buffer.o \
                        sfw/render_core/input_event.o sfw/render_core/input_map.o \
                        sfw/render_core/input.o sfw/render_core/shortcut.o \
                        sfw/render_core/keyboard.o sfw/render_core/font.o \
                        sfw/render_core/color_material_2d.o sfw/render_core/color_material.o \
                        sfw/render_core/colored_material.o sfw/render_core/font_material.o \
                        sfw/render_core/texture_material_2d.o sfw/render_core/texture_material.o \
                        sfw/render_core/transparent_texture_material.o \
                        sfw/render_core/colored_texture_material_2d.o \
                        sfw/render_core/glfw_impl.o \
                        sfw/render_immediate/renderer.o \
                        sfw/render_gui/imgui.o \
                        sfw/render_gui/imgui_draw.o \
                        sfw/render_gui/imgui_impl_glfw.o \
                        sfw/render_gui/imgui_impl_opengl3.o \
                        sfw/render_gui/imgui_tables.o \
                        sfw/render_gui/imgui_widgets.o \
                        sfw/render_gui/gui.o \
                        sfw/game_scene.o sfw/main.o \
                        -o game 

#export args="-lm -ldl -lpthread -lX11 -w -Iengine/ $args"
