

# You might need to add -std=c++14 depending on your compiler version

ccache g++ -Wall -D_REENTRANT -g -I. -c core/aabb.cpp -o core/aabb.o
ccache g++ -Wall -D_REENTRANT -g -I. -c core/basis.cpp -o core/basis.o
ccache g++ -Wall -D_REENTRANT -g -I. -c core/color.cpp -o core/color.o
ccache g++ -Wall -D_REENTRANT -g -I. -c core/face3.cpp -o core/face3.o
ccache g++ -Wall -D_REENTRANT -g -I. -c core/logger.cpp -o core/logger.o
ccache g++ -Wall -D_REENTRANT -g -I. -c core/math_funcs.cpp -o core/math_funcs.o
ccache g++ -Wall -D_REENTRANT -g -I. -c core/memory.cpp -o core/memory.o
ccache g++ -Wall -D_REENTRANT -g -I. -c core/pcg.cpp -o core/pcg.o
ccache g++ -Wall -D_REENTRANT -g -I. -c core/plane.cpp -o core/plane.o
ccache g++ -Wall -D_REENTRANT -g -I. -c core/projection.cpp -o core/projection.o
ccache g++ -Wall -D_REENTRANT -g -I. -c core/quaternion.cpp -o core/quaternion.o
ccache g++ -Wall -D_REENTRANT -g -I. -c core/random_pcg.cpp -o core/random_pcg.o
ccache g++ -Wall -D_REENTRANT -g -I. -c core/rect2.cpp -o core/rect2.o
ccache g++ -Wall -D_REENTRANT -g -I. -c core/rect2i.cpp -o core/rect2i.o
ccache g++ -Wall -D_REENTRANT -g -I. -c core/safe_refcount.cpp -o core/safe_refcount.o
ccache g++ -Wall -D_REENTRANT -g -I. -c core/transform_2d.cpp -o core/transform_2d.o
ccache g++ -Wall -D_REENTRANT -g -I. -c core/transform.cpp -o core/transform.o
ccache g++ -Wall -D_REENTRANT -g -I. -c core/ustring.cpp -o core/ustring.o
ccache g++ -Wall -D_REENTRANT -g -I. -c core/string_name.cpp -o core/string_name.o
ccache g++ -Wall -D_REENTRANT -g -I. -c core/vector2.cpp -o core/vector2.o
ccache g++ -Wall -D_REENTRANT -g -I. -c core/vector2i.cpp -o core/vector2i.o
ccache g++ -Wall -D_REENTRANT -g -I. -c core/vector3.cpp -o core/vector3.o
ccache g++ -Wall -D_REENTRANT -g -I. -c core/vector3i.cpp -o core/vector3i.o
ccache g++ -Wall -D_REENTRANT -g -I. -c core/vector4.cpp -o core/vector4.o
ccache g++ -Wall -D_REENTRANT -g -I. -c core/vector4i.cpp -o core/vector4i.o

ccache g++ -Wall -D_REENTRANT -g -I. -c core/file_access.cpp -o core/file_access.o
ccache g++ -Wall -D_REENTRANT -g -I. -c core/dir_access.cpp -o core/dir_access.o

ccache g++ -Wall -D_REENTRANT -g -I. -c core/pool_vector.cpp -o core/pool_vector.o
ccache g++ -Wall -D_REENTRANT -g -I. -c core/pool_allocator.cpp -o core/pool_allocator.o
ccache g++ -Wall -D_REENTRANT -g -I. -c core/mutex.cpp -o core/mutex.o
ccache g++ -Wall -D_REENTRANT -g -I. -c core/rw_lock.cpp -o core/rw_lock.o
ccache g++ -Wall -D_REENTRANT -g -I. -c core/semaphore.cpp -o core/semaphore.o
ccache g++ -Wall -D_REENTRANT -g -I. -c core/sfw_time.cpp -o core/sfw_time.o
ccache g++ -Wall -D_REENTRANT -g -I. -c core/string_builder.cpp -o core/string_builder.o

ccache g++ -Wall -D_REENTRANT -g -I. -c core/thread.cpp -o core/thread.o
ccache g++ -Wall -D_REENTRANT -g -I. -c core/socket.cpp -o core/socket.o
ccache g++ -Wall -D_REENTRANT -g -I. -c core/inet_address.cpp -o core/inet_address.o

ccache g++ -Wall -D_REENTRANT -g -I. -c core/sub_process.cpp -o core/sub_process.o

ccache g++ -Wall -D_REENTRANT -g -I. -c core/sfw_core.cpp -o core/sfw_core.o

ccache g++ -Wall -D_REENTRANT -g -I. -c core/os.cpp -o core/os.o

ccache g++ -Wall -D_REENTRANT -g -I. -c object/object.cpp -o object/object.o
ccache g++ -Wall -D_REENTRANT -g -I. -c object/reference.cpp -o object/reference.o
ccache g++ -Wall -D_REENTRANT -g -I. -c object/core_string_names.cpp -o object/core_string_names.o
ccache g++ -Wall -D_REENTRANT -g -I. -c object/variant.cpp -o object/variant.o
ccache g++ -Wall -D_REENTRANT -g -I. -c object/variant_op.cpp -o object/variant_op.o
ccache g++ -Wall -D_REENTRANT -g -I. -c object/psignal.cpp -o object/psignal.o
ccache g++ -Wall -D_REENTRANT -g -I. -c object/array.cpp -o object/array.o
ccache g++ -Wall -D_REENTRANT -g -I. -c object/dictionary.cpp -o object/dictionary.o
ccache g++ -Wall -D_REENTRANT -g -I. -c object/ref_ptr.cpp -o object/ref_ptr.o
ccache g++ -Wall -D_REENTRANT -g -I. -c object/resource.cpp -o object/resource.o

ccache g++ -Wall -D_REENTRANT -g -I. -c render_core/application.cpp -o render_core/application.o
ccache g++ -Wall -D_REENTRANT -g -I. -c render_core/scene.cpp -o render_core/scene.o
ccache g++ -Wall -D_REENTRANT -g -I. -c render_core/app_window.cpp -o render_core/app_window.o

ccache g++ -Wall -D_REENTRANT -g -I. -c render_core/shader.cpp -o render_core/shader.o
ccache g++ -Wall -D_REENTRANT -g -I. -c render_core/material.cpp -o render_core/material.o
ccache g++ -Wall -D_REENTRANT -g -I. -c render_core/mesh.cpp -o render_core/mesh.o
ccache g++ -Wall -D_REENTRANT -g -I. -c render_core/mesh_utils.cpp -o render_core/mesh_utils.o
ccache g++ -Wall -D_REENTRANT -g -I. -c render_core/texture.cpp -o render_core/texture.o
ccache g++ -Wall -D_REENTRANT -g -I. -c render_core/frame_buffer.cpp -o render_core/frame_buffer.o
ccache g++ -Wall -D_REENTRANT -g -I. -c render_core/image.cpp -o render_core/image.o
ccache g++ -Wall -D_REENTRANT -g -I. -c render_core/render_state.cpp -o render_core/render_state.o
ccache g++ -Wall -D_REENTRANT -g -I. -c render_core/keyboard.cpp -o render_core/keyboard.o
ccache g++ -Wall -D_REENTRANT -g -I. -c render_core/input_event.cpp -o render_core/input_event.o
ccache g++ -Wall -D_REENTRANT -g -I. -c render_core/input_map.cpp -o render_core/input_map.o
ccache g++ -Wall -D_REENTRANT -g -I. -c render_core/input.cpp -o render_core/input.o
ccache g++ -Wall -D_REENTRANT -g -I. -c render_core/shortcut.cpp -o render_core/shortcut.o
ccache g++ -Wall -D_REENTRANT -g -I. -c render_core/font.cpp -o render_core/font.o

ccache g++ -Wall -D_REENTRANT -g -I. -c render_core/color_material_2d.cpp -o render_core/color_material_2d.o
ccache g++ -Wall -D_REENTRANT -g -I. -c render_core/color_material.cpp -o render_core/color_material.o
ccache g++ -Wall -D_REENTRANT -g -I. -c render_core/colored_material.cpp -o render_core/colored_material.o
ccache g++ -Wall -D_REENTRANT -g -I. -c render_core/font_material.cpp -o render_core/font_material.o
ccache g++ -Wall -D_REENTRANT -g -I. -c render_core/texture_material_2d.cpp -o render_core/texture_material_2d.o
ccache g++ -Wall -D_REENTRANT -g -I. -c render_core/texture_material.cpp -o render_core/texture_material.o
ccache g++ -Wall -D_REENTRANT -g -I. -c render_core/transparent_texture_material.cpp -o render_core/transparent_texture_material.o
ccache g++ -Wall -D_REENTRANT -g -I. -c render_core/colored_texture_material_2d.cpp -o render_core/colored_texture_material_2d.o

#ccache g++ -Wall -D_REENTRANT -g -I. -c render_immediate/renderer.cpp -o render_immediate/renderer.o

#ccache g++ -Wall -D_REENTRANT -g -I. -c render_gui/imgui.cpp -o render_gui/imgui.o
#ccache g++ -Wall -D_REENTRANT -g -I. -c render_gui/imgui_draw.cpp -o render_gui/imgui_draw.o
#ccache g++ -Wall -D_REENTRANT -g -I. -c render_gui/imgui_impl_glfw.cpp -o render_gui/imgui_impl_glfw.o
#ccache g++ -Wall -D_REENTRANT -g -I. -c render_gui/imgui_impl_opengl3.cpp -o render_gui/imgui_impl_opengl3.o
#ccache g++ -Wall -D_REENTRANT -g -I. -c render_gui/imgui_tables.cpp -o render_gui/imgui_tables.o
#ccache g++ -Wall -D_REENTRANT -g -I. -c render_gui/imgui_widgets.cpp -o render_gui/imgui_widgets.o
#ccache g++ -Wall -D_REENTRANT -g -I. -c render_gui/gui.cpp -o render_gui/gui.o

ccache g++ -Wall -D_REENTRANT -g -I. -c game_scene.cpp -o game_scene.o
ccache g++ -Wall -D_REENTRANT -g -I. -c main.cpp -o main.o

# You might need to add -lpthread and/or -latomic depending on your compiler version (add it near -lX11)

ccache g++ -Wall -D_REENTRANT -g core/aabb.o core/basis.o core/color.o \
                        core/face3.o core/logger.o core/math_funcs.o \
                        core/memory.o core/pcg.o core/plane.o core/projection.o core/quaternion.o core/random_pcg.o \
                        core/rect2.o core/rect2i.o core/safe_refcount.o core/transform_2d.o core/transform.o \
                        core/ustring.o core/string_name.o \
                        core/vector2.o core/vector2i.o core/vector3.o \
                        core/vector3i.o core/vector4.o core/vector4i.o \
                        core/pool_vector.o core/pool_allocator.o core/mutex.o core/rw_lock.o core/semaphore.o core/sfw_time.o \
												core/string_builder.o \
                        core/dir_access.o core/file_access.o core/thread.o \
                        core/socket.o core/inet_address.o \
                        core/sub_process.o \
                        core/sfw_core.o \
                        core/os.o \
                        object/object.o object/reference.o object/core_string_names.o \
                        object/variant.o object/variant_op.o object/psignal.o \
                        object/array.o object/dictionary.o object/ref_ptr.o \
                        object/resource.o \
                        render_core/image.o render_core/render_state.o \
                        render_core/application.o render_core/scene.o render_core/app_window.o \
                        render_core/shader.o render_core/material.o render_core/mesh.o \
                        render_core/mesh_utils.o render_core/texture.o \
                        render_core/frame_buffer.o \
                        render_core/input_event.o render_core/input_map.o \
                        render_core/input.o render_core/shortcut.o \
                        render_core/keyboard.o render_core/font.o \
                        render_core/color_material_2d.o render_core/color_material.o \
                        render_core/colored_material.o render_core/font_material.o \
                        render_core/texture_material_2d.o render_core/texture_material.o \
                        render_core/transparent_texture_material.o \
                        render_core/colored_texture_material_2d.o \
                        game_scene.o main.o \
                        -lX11 \
                        -o game 


                        #render_immediate/renderer.o \
                        #render_gui/imgui.o \
                        #render_gui/imgui_draw.o \
                        #render_gui/imgui_impl_glfw.o \
                        #render_gui/imgui_impl_opengl3.o \
                        #render_gui/imgui_tables.o \
                        #render_gui/imgui_widgets.o \
                        #render_gui/gui.o \

