@echo off

if not defined DevEnvDir (
	call "C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvarsall.bat" amd64
)

rem debug: /Zi (== -g)

rem you might need to add /std:c++14 depending on your compiler version.

cl /D_REENTRANT /EHsc /Zi /I. /c core/aabb.cpp /Fo:core/aabb.obj
cl /D_REENTRANT /EHsc /Zi /I. /c core/basis.cpp /Fo:core/basis.obj
cl /D_REENTRANT /EHsc /Zi /I. /c core/color.cpp /Fo:core/color.obj
cl /D_REENTRANT /EHsc /Zi /I. /c core/face3.cpp /Fo:core/face3.obj
cl /D_REENTRANT /EHsc /Zi /I. /c core/logger.cpp /Fo:core/logger.obj
cl /D_REENTRANT /EHsc /Zi /I. /c core/math_funcs.cpp /Fo:core/math_funcs.obj
cl /D_REENTRANT /EHsc /Zi /I. /c core/memory.cpp /Fo:core/memory.obj
cl /D_REENTRANT /EHsc /Zi /I. /c core/pcg.cpp /Fo:core/pcg.obj
cl /D_REENTRANT /EHsc /Zi /I. /c core/plane.cpp /Fo:core/plane.obj
cl /D_REENTRANT /EHsc /Zi /I. /c core/projection.cpp /Fo:core/projection.obj
cl /D_REENTRANT /EHsc /Zi /I. /c core/quaternion.cpp /Fo:core/quaternion.obj
cl /D_REENTRANT /EHsc /Zi /I. /c core/random_pcg.cpp /Fo:core/random_pcg.obj
cl /D_REENTRANT /EHsc /Zi /I. /c core/rect2.cpp /Fo:core/rect2.obj
cl /D_REENTRANT /EHsc /Zi /I. /c core/rect2i.cpp /Fo:core/rect2i.obj
cl /D_REENTRANT /EHsc /Zi /I. /c core/safe_refcount.cpp /Fo:core/safe_refcount.obj
cl /D_REENTRANT /EHsc /Zi /I. /c core/transform_2d.cpp /Fo:core/transform_2d.obj
cl /D_REENTRANT /EHsc /Zi /I. /c core/transform.cpp /Fo:core/transform.obj
cl /D_REENTRANT /EHsc /Zi /I. /c core/ustring.cpp /Fo:core/ustring.obj
cl /D_REENTRANT /EHsc /Zi /I. /c core/string_name.cpp /Fo:core/string_name.obj
cl /D_REENTRANT /EHsc /Zi /I. /c core/vector2.cpp /Fo:core/vector2.obj
cl /D_REENTRANT /EHsc /Zi /I. /c core/vector2i.cpp /Fo:core/vector2i.obj
cl /D_REENTRANT /EHsc /Zi /I. /c core/vector3.cpp /Fo:core/vector3.obj
cl /D_REENTRANT /EHsc /Zi /I. /c core/vector3i.cpp /Fo:core/vector3i.obj
cl /D_REENTRANT /EHsc /Zi /I. /c core/vector4.cpp /Fo:core/vector4.obj
cl /D_REENTRANT /EHsc /Zi /I. /c core/vector4i.cpp /Fo:core/vector4i.obj

cl /D_REENTRANT /EHsc /Zi /I. /c core/file_access.cpp /Fo:core/file_access.obj
cl /D_REENTRANT /EHsc /Zi /I. /c core/dir_access.cpp /Fo:core/dir_access.obj

cl /D_REENTRANT /EHsc /Zi /I. /c core/pool_vector.cpp /Fo:core/pool_vector.obj
cl /D_REENTRANT /EHsc /Zi /I. /c core/pool_allocator.cpp /Fo:core/pool_allocator.obj
cl /D_REENTRANT /EHsc /Zi /I. /c core/mutex.cpp /Fo:core/mutex.obj
cl /D_REENTRANT /EHsc /Zi /I. /c core/rw_lock.cpp /Fo:core/rw_lock.obj
cl /D_REENTRANT /EHsc /Zi /I. /c core/semaphore.cpp /Fo:core/semaphore.obj
cl /D_REENTRANT /EHsc /Zi /I. /c core/sfw_time.cpp /Fo:core/sfw_time.obj
cl /D_REENTRANT /EHsc /Zi /I. /c core/string_builder.cpp /Fo:core/string_builder.obj

cl /D_REENTRANT /EHsc /Zi /I. /c core/thread.cpp /Fo:core/thread.obj
cl /D_REENTRANT /EHsc /Zi /I. /c core/socket.cpp /Fo:core/socket.obj
cl /D_REENTRANT /EHsc /Zi /I. /c core/inet_address.cpp /Fo:core/inet_address.obj

cl /D_REENTRANT /EHsc /Zi /I. /c core/sub_process.cpp /Fo:core/sub_process.obj

cl /D_REENTRANT /EHsc /Zi /I. /c core/sfw_core.cpp /Fo:core/sfw_core.obj

cl /D_REENTRANT /EHsc /Zi /I. /c core/os.cpp /Fo:core/os.obj

cl /D_REENTRANT /EHsc /Zi /I. /c object/object.cpp /Fo:object/object.obj
cl /D_REENTRANT /EHsc /Zi /I. /c object/reference.cpp /Fo:object/reference.obj
cl /D_REENTRANT /EHsc /Zi /I. /c object/core_string_names.cpp /Fo:object/core_string_names.obj
cl /D_REENTRANT /EHsc /Zi /I. /c object/variant.cpp /Fo:object/variant.obj
cl /D_REENTRANT /EHsc /Zi /I. /c object/variant_op.cpp /Fo:object/variant_op.obj
cl /D_REENTRANT /EHsc /Zi /I. /c object/psignal.cpp /Fo:object/psignal.obj
cl /D_REENTRANT /EHsc /Zi /I. /c object/array.cpp /Fo:object/array.obj
cl /D_REENTRANT /EHsc /Zi /I. /c object/dictionary.cpp /Fo:object/dictionary.obj
cl /D_REENTRANT /EHsc /Zi /I. /c object/ref_ptr.cpp /Fo:object/ref_ptr.obj
cl /D_REENTRANT /EHsc /Zi /I. /c object/resource.cpp /Fo:object/resource.obj


cl /D_REENTRANT /EHsc /Zi /I. /c render_core/application.cpp /Fo:render_core/application.obj
cl /D_REENTRANT /EHsc /Zi /I. /c render_core/scene.cpp /Fo:render_core/scene.obj
cl /D_REENTRANT /EHsc /Zi /I. /c render_core/app_window.cpp /Fo:render_core/app_window.obj


cl /D_REENTRANT /EHsc /Zi /I. /c render_core/shader.cpp /Fo:render_core/shader.obj
cl /D_REENTRANT /EHsc /Zi /I. /c render_core/material.cpp /Fo:render_core/material.obj
cl /D_REENTRANT /EHsc /Zi /I. /c render_core/mesh.cpp /Fo:render_core/mesh.obj
cl /D_REENTRANT /EHsc /Zi /I. /c render_core/mesh_utils.cpp /Fo:render_core/mesh_utils.obj
cl /D_REENTRANT /EHsc /Zi /I. /c render_core/texture.cpp /Fo:render_core/texture.obj
cl /D_REENTRANT /EHsc /Zi /I. /c render_core/frame_buffer.cpp /Fo:render_core/frame_buffer.obj
cl /D_REENTRANT /EHsc /Zi /I. /c render_core/image.cpp /Fo:render_core/image.obj
cl /D_REENTRANT /EHsc /Zi /I. /c render_core/render_state.cpp /Fo:render_core/render_state.obj
cl /D_REENTRANT /EHsc /Zi /I. /c render_core/keyboard.cpp /Fo:render_core/keyboard.obj
cl /D_REENTRANT /EHsc /Zi /I. /c render_core/input_event.cpp /Fo:render_core/input_event.obj
cl /D_REENTRANT /EHsc /Zi /I. /c render_core/input_map.cpp /Fo:render_core/input_map.obj
cl /D_REENTRANT /EHsc /Zi /I. /c render_core/input.cpp /Fo:render_core/input.obj
cl /D_REENTRANT /EHsc /Zi /I. /c render_core/shortcut.cpp /Fo:render_core/shortcut.obj
cl /D_REENTRANT /EHsc /Zi /I. /c render_core/font.cpp /Fo:render_core/font.obj

cl /D_REENTRANT /EHsc /Zi /I. /c render_core/color_material_2d.cpp /Fo:render_core/color_material_2d.obj
cl /D_REENTRANT /EHsc /Zi /I. /c render_core/color_material.cpp /Fo:render_core/color_material.obj
cl /D_REENTRANT /EHsc /Zi /I. /c render_core/colored_material.cpp /Fo:render_core/colored_material.obj
cl /D_REENTRANT /EHsc /Zi /I. /c render_core/font_material.cpp /Fo:render_core/font_material.obj
cl /D_REENTRANT /EHsc /Zi /I. /c render_core/texture_material_2d.cpp /Fo:render_core/texture_material_2d.obj
cl /D_REENTRANT /EHsc /Zi /I. /c render_core/texture_material.cpp /Fo:render_core/texture_material.obj
cl /D_REENTRANT /EHsc /Zi /I. /c render_core/transparent_texture_material.cpp /Fo:render_core/transparent_texture_material.obj
cl /D_REENTRANT /EHsc /Zi /I. /c render_core/colored_texture_material_2d.cpp /Fo:render_core/colored_texture_material_2d.obj

cl /D_REENTRANT /EHsc /Zi /I. /c render_immediate/renderer.cpp /Fo:render_immediate/renderer.obj

cl /D_REENTRANT /EHsc /Zi /I. /c render_gui/imgui.cpp /Fo:render_gui/imgui.obj
cl /D_REENTRANT /EHsc /Zi /I. /c render_gui/imgui_draw.cpp /Fo:render_gui/imgui_draw.obj
cl /D_REENTRANT /EHsc /Zi /I. /c render_gui/imgui_impl_glfw.cpp /Fo:render_gui/imgui_impl_glfw.obj
cl /D_REENTRANT /EHsc /Zi /I. /c render_gui/imgui_impl_opengl3.cpp /Fo:render_gui/imgui_impl_opengl3.obj
cl /D_REENTRANT /EHsc /Zi /I. /c render_gui/imgui_tables.cpp /Fo:render_gui/imgui_tables.obj
cl /D_REENTRANT /EHsc /Zi /I. /c render_gui/imgui_widgets.cpp /Fo:render_gui/imgui_widgets.obj
cl /D_REENTRANT /EHsc /Zi /I. /c render_gui/gui.cpp /Fo:render_gui/gui.obj

cl /D_REENTRANT /EHsc /Zi /I. /c game_scene.cpp /Fo:game_scene.obj
cl /D_REENTRANT /EHsc /Zi /I. /c main.cpp /Fo:main.obj


cl /D_REENTRANT /Zi ^
		/EHsc ^
		/Fegame-vc.exe ^
		core/aabb.obj core/basis.obj core/color.obj ^
		core/face3.obj core/logger.obj core/math_funcs.obj ^
		core/memory.obj core/pcg.obj core/plane.obj core/projection.obj core/quaternion.obj core/random_pcg.obj ^
		core/rect2.obj core/rect2i.obj core/safe_refcount.obj core/transform_2d.obj core/transform.obj ^
		core/ustring.obj core/string_name.obj ^
		core/vector2.obj core/vector2i.obj core/vector3.obj ^
		core/vector3i.obj core/vector4.obj core/vector4i.obj ^
		core/pool_vector.obj core/pool_allocator.obj core/mutex.obj core/sfw_time.obj ^
		core/string_builder.obj ^
		core/rw_lock.obj core/semaphore.obj ^
		core/dir_access.obj core/file_access.obj core/thread.obj ^
		core/socket.obj core/inet_address.obj ^
		core/sub_process.obj ^
		core/sfw_core.obj ^
		core/os.obj ^
		object/object.obj object/reference.obj object/core_string_names.obj ^
		object/variant.obj object/variant_op.obj object/psignal.obj ^
		object/array.obj object/dictionary.obj object/ref_ptr.obj ^
		object/resource.obj ^
		render_core/image.obj render_core/render_state.obj ^
		render_core/application.obj render_core/scene.obj render_core/app_window.obj ^
		render_core/shader.obj render_core/material.obj render_core/mesh.obj ^
		render_core/mesh_utils.obj render_core/texture.obj ^
		render_core/frame_buffer.obj ^
		render_core/input_event.obj render_core/input_map.obj ^
		render_core/input.obj render_core/shortcut.obj ^
		render_core/keyboard.obj render_core/font.obj ^
		render_core/color_material_2d.obj render_core/color_material.obj ^
		render_core/colored_material.obj render_core/font_material.obj ^
		render_core/texture_material_2d.obj render_core/texture_material.obj ^
		render_core/transparent_texture_material.obj ^
		render_core/colored_texture_material_2d.obj ^
		render_immediate/renderer.obj ^
		render_gui/imgui.obj ^
		render_gui/imgui_draw.obj ^
		render_gui/imgui_impl_glfw.obj ^
		render_gui/imgui_impl_opengl3.obj ^
		render_gui/imgui_tables.obj ^
		render_gui/imgui_widgets.obj ^
		render_gui/gui.obj ^
		game_scene.obj main.obj ^
		/SUBSYSTEM:CONSOLE
