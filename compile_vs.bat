@echo off

if not defined DevEnvDir (
	call "C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvarsall.bat" amd64
)

rem debug: /Zi (== -g)

rem TODO reentrant is probably not needed

cl /D_REENTRANT /EHsc /Zi /Isfw /c sfw/core/aabb.cpp /Fo:sfw/core/aabb.obj
cl /D_REENTRANT /EHsc /Zi /Isfw /c sfw/core/basis.cpp /Fo:sfw/core/basis.obj
cl /D_REENTRANT /EHsc /Zi /Isfw /c sfw/core/color.cpp /Fo:sfw/core/color.obj
cl /D_REENTRANT /EHsc /Zi /Isfw /c sfw/core/face3.cpp /Fo:sfw/core/face3.obj
cl /D_REENTRANT /EHsc /Zi /Isfw /c sfw/core/logger.cpp /Fo:sfw/core/logger.obj
cl /D_REENTRANT /EHsc /Zi /Isfw /c sfw/core/math_funcs.cpp /Fo:sfw/core/math_funcs.obj
cl /D_REENTRANT /EHsc /Zi /Isfw /c sfw/core/memory.cpp /Fo:sfw/core/memory.obj
cl /D_REENTRANT /EHsc /Zi /Isfw /c sfw/core/pcg.cpp /Fo:sfw/core/pcg.obj
cl /D_REENTRANT /EHsc /Zi /Isfw /c sfw/core/plane.cpp /Fo:sfw/core/plane.obj
cl /D_REENTRANT /EHsc /Zi /Isfw /c sfw/core/projection.cpp /Fo:sfw/core/projection.obj
cl /D_REENTRANT /EHsc /Zi /Isfw /c sfw/core/quaternion.cpp /Fo:sfw/core/quaternion.obj
cl /D_REENTRANT /EHsc /Zi /Isfw /c sfw/core/random_pcg.cpp /Fo:sfw/core/random_pcg.obj
cl /D_REENTRANT /EHsc /Zi /Isfw /c sfw/core/rect2.cpp /Fo:sfw/core/rect2.obj
cl /D_REENTRANT /EHsc /Zi /Isfw /c sfw/core/rect2i.cpp /Fo:sfw/core/rect2i.obj
cl /D_REENTRANT /EHsc /Zi /Isfw /c sfw/core/safe_refcount.cpp /Fo:sfw/core/safe_refcount.obj
cl /D_REENTRANT /EHsc /Zi /Isfw /c sfw/core/transform_2d.cpp /Fo:sfw/core/transform_2d.obj
cl /D_REENTRANT /EHsc /Zi /Isfw /c sfw/core/transform.cpp /Fo:sfw/core/transform.obj
cl /D_REENTRANT /EHsc /Zi /Isfw /c sfw/core/ustring.cpp /Fo:sfw/core/ustring.obj
cl /D_REENTRANT /EHsc /Zi /Isfw /c sfw/core/string_name.cpp /Fo:sfw/core/string_name.obj
cl /D_REENTRANT /EHsc /Zi /Isfw /c sfw/core/vector2.cpp /Fo:sfw/core/vector2.obj
cl /D_REENTRANT /EHsc /Zi /Isfw /c sfw/core/vector2i.cpp /Fo:sfw/core/vector2i.obj
cl /D_REENTRANT /EHsc /Zi /Isfw /c sfw/core/vector3.cpp /Fo:sfw/core/vector3.obj
cl /D_REENTRANT /EHsc /Zi /Isfw /c sfw/core/vector3i.cpp /Fo:sfw/core/vector3i.obj
cl /D_REENTRANT /EHsc /Zi /Isfw /c sfw/core/vector4.cpp /Fo:sfw/core/vector4.obj
cl /D_REENTRANT /EHsc /Zi /Isfw /c sfw/core/vector4i.cpp /Fo:sfw/core/vector4i.obj

cl /D_REENTRANT /EHsc /Zi /Isfw /c sfw/core/file_access.cpp /Fo:sfw/core/file_access.obj
cl /D_REENTRANT /EHsc /Zi /Isfw /c sfw/core/dir_access.cpp /Fo:sfw/core/dir_access.obj

cl /D_REENTRANT /EHsc /Zi /Isfw /c sfw/core/pool_vector.cpp /Fo:sfw/core/pool_vector.obj
cl /D_REENTRANT /EHsc /Zi /Isfw /c sfw/core/pool_allocator.cpp /Fo:sfw/core/pool_allocator.obj
cl /D_REENTRANT /EHsc /Zi /Isfw /c sfw/core/mutex.cpp /Fo:sfw/core/mutex.obj
cl /D_REENTRANT /EHsc /Zi /Isfw /c sfw/core/sfw_time.cpp /Fo:sfw/core/sfw_time.obj

cl /D_REENTRANT /EHsc /Zi /Isfw /c sfw/core/thread.cpp /Fo:sfw/core/thread.obj
cl /D_REENTRANT /EHsc /Zi /Isfw /c sfw/core/socket.cpp /Fo:sfw/core/socket.obj
cl /D_REENTRANT /EHsc /Zi /Isfw /c sfw/core/inet_address.cpp /Fo:sfw/core/inet_address.obj

cl /D_REENTRANT /EHsc /Zi /Isfw /c sfw/core/sub_process.cpp /Fo:sfw/core/sub_process.obj

cl /D_REENTRANT /EHsc /Zi /Isfw /c sfw/core/sfw_core.cpp /Fo:sfw/core/sfw_core.obj

cl /D_REENTRANT /EHsc /Zi /Isfw /c sfw/object/object.cpp /Fo:sfw/object/object.obj
cl /D_REENTRANT /EHsc /Zi /Isfw /c sfw/object/reference.cpp /Fo:sfw/object/reference.obj
cl /D_REENTRANT /EHsc /Zi /Isfw /c sfw/object/core_string_names.cpp /Fo:sfw/object/core_string_names.obj
cl /D_REENTRANT /EHsc /Zi /Isfw /c sfw/object/variant.cpp /Fo:sfw/object/variant.obj
cl /D_REENTRANT /EHsc /Zi /Isfw /c sfw/object/variant_op.cpp /Fo:sfw/object/variant_op.obj
cl /D_REENTRANT /EHsc /Zi /Isfw /c sfw/object/psignal.cpp /Fo:sfw/object/psignal.obj
cl /D_REENTRANT /EHsc /Zi /Isfw /c sfw/object/array.cpp /Fo:sfw/object/array.obj
cl /D_REENTRANT /EHsc /Zi /Isfw /c sfw/object/dictionary.cpp /Fo:sfw/object/dictionary.obj
cl /D_REENTRANT /EHsc /Zi /Isfw /c sfw/object/ref_ptr.cpp /Fo:sfw/object/ref_ptr.obj
cl /D_REENTRANT /EHsc /Zi /Isfw /c sfw/object/resource.cpp /Fo:sfw/object/resource.obj


cl /D_REENTRANT /EHsc /Zi /Isfw /c sfw/render_core/application.cpp /Fo:sfw/render_core/application.obj
cl /D_REENTRANT /EHsc /Zi /Isfw /c sfw/render_core/scene.cpp /Fo:sfw/render_core/scene.obj
cl /D_REENTRANT /EHsc /Zi /Isfw /c sfw/render_core/app_window.cpp /Fo:sfw/render_core/app_window.obj


cl /D_REENTRANT /EHsc /Zi /Isfw /c sfw/render_core/shader.cpp /Fo:sfw/render_core/shader.obj
cl /D_REENTRANT /EHsc /Zi /Isfw /c sfw/render_core/material.cpp /Fo:sfw/render_core/material.obj
cl /D_REENTRANT /EHsc /Zi /Isfw /c sfw/render_core/mesh.cpp /Fo:sfw/render_core/mesh.obj
cl /D_REENTRANT /EHsc /Zi /Isfw /c sfw/render_core/mesh_utils.cpp /Fo:sfw/render_core/mesh_utils.obj
cl /D_REENTRANT /EHsc /Zi /Isfw /c sfw/render_core/texture.cpp /Fo:sfw/render_core/texture.obj
cl /D_REENTRANT /EHsc /Zi /Isfw /c sfw/render_core/image.cpp /Fo:sfw/render_core/image.obj
cl /D_REENTRANT /EHsc /Zi /Isfw /c sfw/render_core/render_state.cpp /Fo:sfw/render_core/render_state.obj
cl /D_REENTRANT /EHsc /Zi /Isfw /c sfw/render_core/keyboard.cpp /Fo:sfw/render_core/keyboard.obj
cl /D_REENTRANT /EHsc /Zi /Isfw /c sfw/render_core/input_event.cpp /Fo:sfw/render_core/input_event.obj
cl /D_REENTRANT /EHsc /Zi /Isfw /c sfw/render_core/input_map.cpp /Fo:sfw/render_core/input_map.obj
cl /D_REENTRANT /EHsc /Zi /Isfw /c sfw/render_core/input.cpp /Fo:sfw/render_core/input.obj
cl /D_REENTRANT /EHsc /Zi /Isfw /c sfw/render_core/shortcut.cpp /Fo:sfw/render_core/shortcut.obj
cl /D_REENTRANT /EHsc /Zi /Isfw /c sfw/render_core/font.cpp /Fo:sfw/render_core/font.obj

cl /D_REENTRANT /EHsc /Zi /Isfw /c sfw/render_core/color_material_2d.cpp /Fo:sfw/render_core/color_material_2d.obj
cl /D_REENTRANT /EHsc /Zi /Isfw /c sfw/render_core/color_material.cpp /Fo:sfw/render_core/color_material.obj
cl /D_REENTRANT /EHsc /Zi /Isfw /c sfw/render_core/colored_material.cpp /Fo:sfw/render_core/colored_material.obj
cl /D_REENTRANT /EHsc /Zi /Isfw /c sfw/render_core/font_material.cpp /Fo:sfw/render_core/font_material.obj
cl /D_REENTRANT /EHsc /Zi /Isfw /c sfw/render_core/texture_material_2d.cpp /Fo:sfw/render_core/texture_material_2d.obj
cl /D_REENTRANT /EHsc /Zi /Isfw /c sfw/render_core/texture_material.cpp /Fo:sfw/render_core/texture_material.obj
cl /D_REENTRANT /EHsc /Zi /Isfw /c sfw/render_core/transparent_texture_material.cpp /Fo:sfw/render_core/transparent_texture_material.obj

cl /D_REENTRANT /EHsc /Zi /Isfw /c sfw/render_immediate/renderer.cpp /Fo:sfw/render_immediate/renderer.obj

cl /D_REENTRANT /EHsc /Zi /Isfw /c sfw/render_objects/camera_3d.cpp /Fo:sfw/render_objects/camera_3d.obj
cl /D_REENTRANT /EHsc /Zi /Isfw /c sfw/render_objects/object_3d.cpp /Fo:sfw/render_objects/object_3d.obj
cl /D_REENTRANT /EHsc /Zi /Isfw /c sfw/render_objects/mesh_instance_3d.cpp /Fo:sfw/render_objects/mesh_instance_3d.obj

cl /D_REENTRANT /EHsc /Zi /Isfw /c sfw/render_objects/camera_2d.cpp /Fo:sfw/render_objects/camera_2d.obj
cl /D_REENTRANT /EHsc /Zi /Isfw /c sfw/render_objects/mesh_instance_2d.cpp /Fo:sfw/render_objects/mesh_instance_2d.obj
cl /D_REENTRANT /EHsc /Zi /Isfw /c sfw/render_objects/object_2d.cpp /Fo:sfw/render_objects/object_2d.obj
cl /D_REENTRANT /EHsc /Zi /Isfw /c sfw/render_objects/sprite.cpp /Fo:sfw/render_objects/sprite.obj
cl /D_REENTRANT /EHsc /Zi /Isfw /c sfw/render_objects/tile_map.cpp /Fo:sfw/render_objects/tile_map.obj
cl /D_REENTRANT /EHsc /Zi /Isfw /c sfw/render_objects/text_2d.cpp /Fo:sfw/render_objects/text_2d.obj

cl /D_REENTRANT /EHsc /Zi /Isfw /c sfw/game_scene.cpp /Fo:sfw/game_scene.obj
cl /D_REENTRANT /EHsc /Zi /Isfw /c sfw/main.cpp /Fo:sfw/main.obj


rem cl main.cpp shader.cpp material.cpp mesh.cpp mesh_instance.cpp mesh_utils.cpp texture.cpp camera.cpp application.cpp scene.cpp game_scene.cpp object_2d.cpp tile_map.cpp sprite.cpp ^
rem	libs\glad\src\glad.c /Febin/game-vc.exe ^
rem	/EHsc ^
rem	/Ilibs\SDL2-VC\include ^
rem	/Ilibs\glad\include ^
rem	/link /LIBPATH:libs\SDL2-VC\lib SDL2.lib SDL2main.lib opengl32.lib ^
rem	/SUBSYSTEM:CONSOLE


cl /D_REENTRANT /Zi ^
		/EHsc ^
		/Fegame-vc.exe ^
		sfw/core/aabb.obj sfw/core/basis.obj sfw/core/color.obj ^
		sfw/core/face3.obj sfw/core/logger.obj sfw/core/math_funcs.obj ^
		sfw/core/memory.obj sfw/core/pcg.obj sfw/core/plane.obj sfw/core/projection.obj sfw/core/quaternion.obj sfw/core/random_pcg.obj ^
		sfw/core/rect2.obj sfw/core/rect2i.obj sfw/core/safe_refcount.obj sfw/core/transform_2d.obj sfw/core/transform.obj ^
		sfw/core/ustring.obj sfw/core/string_name.obj ^
		sfw/core/vector2.obj sfw/core/vector2i.obj sfw/core/vector3.obj ^
		sfw/core/vector3i.obj sfw/core/vector4.obj sfw/core/vector4i.obj ^
		sfw/core/pool_vector.obj sfw/core/pool_allocator.obj sfw/core/mutex.obj sfw/core/sfw_time.obj ^
		sfw/core/dir_access.obj sfw/core/file_access.obj sfw/core/thread.obj ^
		sfw/core/socket.obj sfw/core/inet_address.obj ^
		sfw/core/sub_process.obj ^
		sfw/core/sfw_core.obj ^
		sfw/object/object.obj sfw/object/reference.obj sfw/object/core_string_names.obj ^
		sfw/object/variant.obj sfw/object/variant_op.obj sfw/object/psignal.obj ^
		sfw/object/array.obj sfw/object/dictionary.obj sfw/object/ref_ptr.obj ^
		sfw/object/resource.obj ^
		sfw/render_core/image.obj sfw/render_core/render_state.obj ^
		sfw/render_core/application.obj sfw/render_core/scene.obj sfw/render_core/app_window.obj ^
		sfw/render_core/shader.obj sfw/render_core/material.obj sfw/render_core/mesh.obj ^
		sfw/render_core/mesh_utils.obj sfw/render_core/texture.obj ^
		sfw/render_core/input_event.obj sfw/render_core/input_map.obj ^
		sfw/render_core/input.obj sfw/render_core/shortcut.obj ^
		sfw/render_core/keyboard.obj sfw/render_core/font.obj ^
		sfw/render_core/color_material_2d.obj sfw/render_core/color_material.obj ^
		sfw/render_core/colored_material.obj sfw/render_core/font_material.obj ^
		sfw/render_core/texture_material_2d.obj sfw/render_core/texture_material.obj ^
		sfw/render_core/transparent_texture_material.obj ^
		sfw/render_immediate/renderer.obj ^
		sfw/render_objects/camera_3d.obj sfw/render_objects/object_3d.obj sfw/render_objects/mesh_instance_3d.obj ^
		sfw/render_objects/object_2d.obj ^
		sfw/render_objects/sprite.obj sfw/render_objects/tile_map.obj ^
		sfw/render_objects/camera_2d.obj sfw/render_objects/mesh_instance_2d.obj ^
		sfw/render_objects/text_2d.obj ^
		sfw/game_scene.obj sfw/main.obj ^
		/SUBSYSTEM:CONSOLE
