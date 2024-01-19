

{{FILEINLINE:tools/merger/sfw_readme.inl.h}}
{{FILEINLINE:tools/merger/sfw_linceses_core.inl.h}}
{{FILEINLINE:tools/merger/sfw_linceses_render_core.inl.h}}

#include <cstdio>
#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>
#include <ctime>
#include <wchar.h>
#include <cstdint>
#include <memory.h>

#ifndef SFW_H

#ifdef __APPLE__
#ifndef _APPLE_NO_IMPL_
#define _APPLE_NO_IMPL_
#endif //_APPLE_NO_IMPL_
#endif //__APPLE__

#include "sfw.h"

#ifdef __APPLE__
#undef ONLY_GLAD
#include "sfw_3rd.m"
#endif //__APPLE__

#endif //SFW_H

// On OSX sfw_3rd.m has to be compiled manually on Objective C Mode.
#ifndef __APPLE__

#ifndef SFW_3RD_IMPL
#define SFW_3RD_IMPL

#if defined(__linux__)
//typedef XID Font;
#define Font The_Font_I_dont_care
#endif

#undef ONLY_GLAD
#include "sfw_3rd.m"

#undef CursorShape

#if defined(__linux__)
#undef Font
#undef KEY_ESC
#undef KEY_TICK
#undef KEY_1
#undef KEY_2
#undef KEY_3
#undef KEY_4
#undef KEY_5
#undef KEY_6
#undef KEY_7
#undef KEY_8
#undef KEY_9
#undef KEY_0
#undef KEY_BS
#undef KEY_TAB
#undef KEY_Q
#undef KEY_W
#undef KEY_E
#undef KEY_R
#undef KEY_T
#undef KEY_Y
#undef KEY_U
#undef KEY_I
#undef KEY_O
#undef KEY_P
#undef KEY_CAPS
#undef KEY_A
#undef KEY_S
#undef KEY_D
#undef KEY_F
#undef KEY_G
#undef KEY_H
#undef KEY_J
#undef KEY_K
#undef KEY_L
#undef KEY_ENTER
#undef KEY_LSHIFT
#undef KEY_Z
#undef KEY_X
#undef KEY_C
#undef KEY_V
#undef KEY_B
#undef KEY_N
#undef KEY_M
#undef KEY_RSHIFT
#undef KEY_UP
#undef KEY_LCTRL
#undef KEY_LALT
#undef KEY_SPACE
#undef KEY_RALT
#undef KEY_RCTRL
#undef KEY_LEFT
#undef KEY_DOWN
#undef KEY_RIGHT
#undef KEY_INS
#undef KEY_HOME
#undef KEY_PGUP
#undef KEY_DEL
#undef KEY_END
#undef KEY_PGDN
#undef KEY_LMETA
#undef KEY_RMETA
#undef KEY_MENU
#undef KEY_PRINT
#undef KEY_PAUSE
#undef KEY_SCROLL
#undef KEY_NUMLOCK
#undef KEY_MINUS
#undef KEY_EQUAL
#undef KEY_LSQUARE
#undef KEY_RSQUARE
#undef KEY_SEMICOLON
#undef KEY_QUOTE
#undef KEY_HASH
#undef KEY_BAR
#undef KEY_COMMA
#undef KEY_DOT
#undef KEY_SLASH
#undef KEY_F1
#undef KEY_F2
#undef KEY_F3
#undef KEY_F4
#undef KEY_F5
#undef KEY_F6
#undef KEY_F7
#undef KEY_F8
#undef KEY_F9
#undef KEY_F10
#undef KEY_F11
#undef KEY_F12
#undef KEY_PAD1
#undef KEY_PAD2
#undef KEY_PAD3
#undef KEY_PAD4
#undef KEY_PAD5
#undef KEY_PAD6
#undef KEY_PAD7
#undef KEY_PAD8
#undef KEY_PAD9
#undef KEY_PAD0
#undef KEY_PADADD
#undef KEY_PADSUB
#undef KEY_PADMUL
#undef KEY_PADDIV
#undef KEY_PADDOT
#undef KEY_PADENTER
#undef MOUSE_L
#undef MOUSE_M
#undef MOUSE_R
#undef GAMEPAD_CONNECTED
#undef GAMEPAD_A
#undef GAMEPAD_B
#undef GAMEPAD_X
#undef GAMEPAD_Y
#undef GAMEPAD_UP
#undef GAMEPAD_DOWN
#undef GAMEPAD_LEFT
#undef GAMEPAD_RIGHT
#undef GAMEPAD_MENU
#undef GAMEPAD_START
#undef GAMEPAD_LB
#undef GAMEPAD_RB
#undef GAMEPAD_LTHUMB
#undef GAMEPAD_RTHUMB
#undef WINDOW_BLUR
#undef WINDOW_FOCUS
#undef WINDOW_CLOSE
#undef WINDOW_MINIMIZE
#undef WINDOW_MAXIMIZE
#undef WINDOW_FULLSCREEN
#undef WINDOW_WINDOWED
#undef GAMEPAD_LPAD
#undef GAMEPAD_LPAD
#undef GAMEPAD_LPADY
#undef GAMEPAD_RPAD
#undef GAMEPAD_RPAD
#undef GAMEPAD_RPADY
#undef GAMEPAD_LT
#undef GAMEPAD_RT
#undef GAMEPAD_BATTERY
#undef MOUSE
#undef MOUSE
#undef MOUSE_Y
#undef MOUSE_W
#undef TOUCH_X1
#undef TOUCH_Y1
#undef TOUCH_X2
#undef TOUCH_Y2
#undef WINDOW_RESIZE
#undef WINDOW_RESIZE
#undef WINDOW_RESIZEY
#undef WINDOW_ORIENTATION
#undef WINDOW_BATTERY
#undef GAMEPAD_GUID
#undef GAMEPAD_NAME
#endif

#endif //SFW_3RD_IMPL

#endif // #ifndef __APPLE__

//===================  CORE SECTION  ===================

{{FILE:sfw/core/ucaps.h}}

//--STRIP
//#include "core/mutex.h"
//--STRIP
{{FILE:sfw/core/mutex.cpp}}
//--STRIP
//#if defined(DEBUG_ENABLED) && !defined(NO_THREADS)
//#include "core/safe_refcount.h"
//#include "core/error/error_macros.h"
//--STRIP
{{FILE:sfw/core/safe_refcount.cpp}}
//--STRIP
//--STRIP
//#include "thread.h"
//#include "core/error_macros.h"
//#include "core/safe_refcount.h"
//--STRIP
//--STRIP
{{FILE:sfw/core/thread.cpp}}

//--STRIP
//#include "core/sfw_time.h"
//--STRIP
{{FILE:sfw/core/sfw_time.cpp}}

//--STRIP
//#include "core/memory.h"
//#include "core/error_macros.h"
//#include "core/safe_refcount.h"
//--STRIP
{{FILE:sfw/core/memory.cpp}}
//--STRIP
//{//{//FILE:sfw/core/old/directory.cpp}}
//--STRIP

//--STRIP
//#include "core/pool_vector.h"
//--STRIP
{{FILE:sfw/core/pool_vector.cpp}}
//--STRIP
//#include "pool_allocator.h"
//#include "core/error_macros.h"
//#include "core/memory.h"
//--STRIP
{{FILE:sfw/core/pool_allocator.cpp}}

//--STRIP
//#include "core/random_pcg.h"
//#include "core/sfw_time.h"
//#include "core/error_macros.h"
//--STRIP
{{FILE:sfw/core/random_pcg.cpp}}

//--STRIP
//#include "core/math_funcs.h"
//#include "core/error_macros.h"
//--STRIP
{{FILE:sfw/core/math_funcs.cpp}}

//--STRIP
//#include "core/ustring.h"
//#include "core/color.h"
//#include "core/math_funcs.h"
//#include "core/memory.h"
//#include "ucaps.h"
//--STRIP
{{FILE:sfw/core/ustring.cpp}}
//--STRIP
//#include "core/logger.h"
//#include "core/ustring.h"
//--STRIP
{{FILE:sfw/core/logger.cpp}}
//--STRIP
//#include "core/string_name.h"
//--STRIP
{{FILE:sfw/core/string_name.cpp}}

//--STRIP
//#include "core/aabb.h"
//--STRIP
{{FILE:sfw/core/aabb.cpp}}
//--STRIP
//#include "core/vector3i.h"
//#include "core/vector3.h"
//#include "core/ustring.h"
//--STRIP
{{FILE:sfw/core/vector3i.cpp}}
//--STRIP
//#include "core/transform_2d.h"
//--STRIP
{{FILE:sfw/core/transform_2d.cpp}}
//--STRIP
//#include "core/projection.h"
//#include "core/aabb.h"
//#include "core/math_funcs.h"
//#include "core/plane.h"
//#include "core/rect2.h"
//#include "core/transform.h"
//--STRIP
{{FILE:sfw/core/projection.cpp}}
//--STRIP
//#include "core/vector3.h"
//#include "core/basis.h"
//--STRIP
{{FILE:sfw/core/vector3.cpp}}
//--STRIP
//#include "core/pcg.h"
//--STRIP
{{FILE:sfw/core/pcg.cpp}}
//--STRIP
//#include "core/vector2.h"
//#include "core/ustring.h"
//--STRIP
{{FILE:sfw/core/vector2.cpp}}
//--STRIP
//#include "core/basis.h"
//#include "core/math_funcs.h"
//--STRIP
{{FILE:sfw/core/basis.cpp}}
//--STRIP
//#include "face3.h"
//--STRIP
{{FILE:sfw/core/face3.cpp}}
//--STRIP
//#include "core/vector4i.h"
//#include "core/vector4.h"
//#include "core/ustring.h"
//--STRIP
{{FILE:sfw/core/vector4i.cpp}}
//--STRIP
//#include "core/transform.h"
//#include "core/math_funcs.h"
//--STRIP
{{FILE:sfw/core/transform.cpp}}
//--STRIP
//#include "core/color.h"
//#include "core/math_funcs.h"
//--STRIP
{{FILE:sfw/core/color.cpp}}
//--STRIP
//#include "core/quaternion.h"
//#include "core/basis.h"
//--STRIP
{{FILE:sfw/core/quaternion.cpp}}
//--STRIP
//#include "core/plane.h"
//#include "core/math_funcs.h"
//--STRIP
{{FILE:sfw/core/plane.cpp}}
//--STRIP
//#include "core/vector2i.h"
//#include "core/ustring.h"
//--STRIP
{{FILE:sfw/core/vector2i.cpp}}
//--STRIP
//#include "core/transform_2d.h" // Includes rect2.h but Rect2 needs Transform2D
//#include "core/rect2i.h"
//--STRIP
{{FILE:sfw/core/rect2.cpp}}
//--STRIP
//#include "core/transform_2d.h" // Includes rect2.h but Rect2 needs Transform2D
//--STRIP
{{FILE:sfw/core/rect2i.cpp}}
//--STRIP
//#include "core/vector4.h"
//#include "core/basis.h"
//--STRIP
{{FILE:sfw/core/vector4.cpp}}

//--STRIP
//#include "file_access.h"
//--STRIP
{{FILE:sfw/core/file_access.cpp}}

//--STRIP
//#include "dir_access.h"
//#include "3rd_tinydir.h"
//--STRIP
{{FILE:sfw/core/dir_access.cpp}}

//--STRIP
//System includes
//--STRIP
{{FILE:sfw/core/inet_address.cpp}}
//--STRIP
//#include "core/error_macros.h"
//#include "core/ustring.h"
//--STRIP
{{FILE:sfw/core/socket.cpp}}

//--STRIP
//Win Only
//#include <avrt.h>
//#include <direct.h>
//#include <knownfolders.h>
//#include <process.h>
//#include <regstr.h>
//#include <shlobj.h>
//#include <wchar.h>
//--STRIP
{{FILE:sfw/core/sub_process.cpp}}

//--STRIP
//#include "core/pool_vector.h"
//#include "core/string_name.h"
//--STRIP
{{FILE:sfw/core/sfw_core.cpp}}


//===================  OBJECT SECTION  ===================

//--STRIP
//#include "resource.h"
//--STRIP
{{FILE:sfw/object/resource.cpp}}
//--STRIP
//#include "object/reference.h"
//--STRIP
{{FILE:sfw/object/reference.cpp}}
//--STRIP
//#include "object/object.h"
//#include "core/error_macros.h"
//#include "core/logger.h"
//#include "object/core_string_names.h"
//#include "object/object_rc.h"
//--STRIP
{{FILE:sfw/object/object.cpp}}
//--STRIP
//#include "ref_ptr.h"
//#include "object/reference.h"
//#include "object/resource.h"
//--STRIP
{{FILE:sfw/object/ref_ptr.cpp}}
//--STRIP
//#include "core_string_names.h"
//--STRIP
{{FILE:sfw/object/core_string_names.cpp}}
//--STRIP
//#include "dictionary.h"
//#include "core/ordered_hash_map.h"
//#include "core/safe_refcount.h"
//#include "object/variant.h"
//--STRIP
{{FILE:sfw/object/dictionary.cpp}}
//--STRIP
//#include "array.h"
//#include "core/hashfuncs.h"
//#include "core/vector.h"
//#include "object/object.h"
//#include "object/variant.h"
//#include "core/ustring.h"
//--STRIP
{{FILE:sfw/object/array.cpp}}
//--STRIP
//#include "psignal.h"
//--STRIP
{{FILE:sfw/object/psignal.cpp}}
//--STRIP
//#include "variant.h"
//#include "core/math_funcs.h"
//#include "object/core_string_names.h"
//#include "object/object.h"
//#include "object/object_rc.h"
//#include "object/resource.h"
//--STRIP
{{FILE:sfw/object/variant.cpp}}
//--STRIP
//#include "variant.h"
//#include "object/core_string_names.h"
//#include "object/object.h"
//#include "object/object_rc.h"
//#include "object/resource.h"
//--STRIP
{{FILE:sfw/object/variant_op.cpp}}

//===================  RENDER CORE SECTION  ===================

{{FILE:sfw/render_core/font_data_bm_mini.inc.h}}
{{FILE:sfw/render_core/font_data_tables.inc.h}}

//--STRIP
//#include "render_core/texture.h"
//#include "core/memory.h"
//#include "render_core/app_window.h"
//--STRIP
{{FILE:sfw/render_core/texture.cpp}}
//--STRIP
//#include "render_core/application.h"
//#include "core/math_defs.h"
//#include "core/sfw_time.h"
//#include "render_core/input.h"
//#include "render_core/input_map.h"
//#include "render_core/app_window.h"
//#include "core/pool_vector.h"
//#include "core/string_name.h"
//#include "object/core_string_names.h"
//--STRIP
{{FILE:sfw/render_core/application.cpp}}
//--STRIP
//#include "render_core/shader.h"
//--STRIP
{{FILE:sfw/render_core/shader.cpp}}
//--STRIP
//#include "input_event.h"
//#include "render_core/input_map.h"
//#include "render_core/keyboard.h"
//#include "render_core/shortcut.h"
//--STRIP
{{FILE:sfw/render_core/input_event.cpp}}
//--STRIP
//#include "render_core/mesh.h"
//#include "render_core/shader.h"
//--STRIP
{{FILE:sfw/render_core/mesh.cpp}}
//--STRIP
//#include "font.h"
//#include "app_window.h"
//#include "3rd_glad.h"
//#include "3rd_stb_truetype.h"
//#include "font_data_bm_mini.inc.h"
//#include "font_data_tables.inc.h"
//#include "render_core/image.h"
//#include "render_core/mesh.h"
//#include "render_core/texture.h"
//--STRIP
{{FILE:sfw/render_core/font.cpp}}
//--STRIP
//#include "render_core/render_state.h"
//--STRIP
{{FILE:sfw/render_core/render_state.cpp}}
//--STRIP
//#include "render_core/mesh_utils.h"
//--STRIP
{{FILE:sfw/render_core/mesh_utils.cpp}}
//--STRIP
//#include "shortcut.h"
//#include "render_core/input_event.h"
//--STRIP
{{FILE:sfw/render_core/shortcut.cpp}}
//--STRIP
//{//{FILE:sfw/render_core/primitive_meshes.cpp}}
//--STRIP
//--STRIP
//#include "render_core/material.h"
//--STRIP
{{FILE:sfw/render_core/material.cpp}}


//--STRIP
//#includes own header
//--STRIP
{{FILE:sfw/render_core/color_material_2d.cpp}}
//--STRIP
//#includes own header
//--STRIP
{{FILE:sfw/render_core/color_material.cpp}}
//--STRIP
//#includes own header
//--STRIP
{{FILE:sfw/render_core/colored_material.cpp}}
//--STRIP
//#includes own header
//--STRIP
{{FILE:sfw/render_core/font_material.cpp}}
//--STRIP
//#includes own header
//--STRIP
{{FILE:sfw/render_core/texture_material_2d.cpp}}
//--STRIP
//#includes own header
//--STRIP
{{FILE:sfw/render_core/texture_material.cpp}}
//--STRIP
//#includes own header
//--STRIP
{{FILE:sfw/render_core/transparent_texture_material.cpp}}

//--STRIP
//#include "render_core/image.h"
//#include "core/error_macros.h"
//#include "core/hash_map.h"
//#include "math.h"
//#include "core/memory.h"
//#include "core/vector3.h"
//#include "3rd_stb_image.h"
//#include "3rd_stb_image_write.h"
//--STRIP
{{FILE:sfw/render_core/image.cpp}}
//--STRIP
//#include "render_core/app_window.h"
//#include "render_core/3rd_glad.h"
//#include "3rd_glfw3.h"
//#include "core/error_macros.h"
//#include "core/sfw_time.h"
//#include "core/ustring.h"
//#include "core/vector4.h"
//#include "render_core/application.h"
//#include "render_core/input.h"
//--STRIP
{{FILE:sfw/render_core/app_window.cpp}}
//--STRIP
//#include "keyboard.h"
//--STRIP
{{FILE:sfw/render_core/keyboard.cpp}}
//--STRIP
//#include "input_map.h"
//#include "render_core/input.h"
//#include "render_core/keyboard.h"
//--STRIP
{{FILE:sfw/render_core/input_map.cpp}}
//--STRIP
//#include "render_core/scene.h"
//#include "render_core/input_event.h"
//--STRIP
{{FILE:sfw/render_core/scene.cpp}}
//--STRIP
//#include "input.h"
//#include "core/logger.h"
//#include "core/sfw_time.h"
//#include "render_core/application.h"
//#include "render_core/input_map.h"
//#include "render_core/keyboard.h"
//#include "render_core/texture.h"
//#include "render_core/app_window.h"
//#include "render_core/3rd_glfw3.h"
//--STRIP
{{FILE:sfw/render_core/input.cpp}}

//===================  RENDER IMMEDIATE SECTION  ===================

//--STRIP
//#include "renderer.h"
//#include "render_core/color_material_2d.h"
//#include "render_core/font.h"
//#include "render_core/font_material.h"
//#include "render_core/material.h"
//#include "render_core/mesh.h"
//#include "render_core/texture.h"
//#include "render_core/texture_material_2d.h"
//#include "render_core/app_window.h"
//#include "render_core/render_state.h"
//--STRIP
{{FILE:sfw/render_immediate/renderer.cpp}}

//===================  RENDER OBJCTS SECTION  ===================

//--STRIP
//#include "render_objects/camera_3d.h"
//#include "core/math_funcs.h"
//#include "render_core/render_state.h"
//--STRIP
{{FILE:sfw/render_objects/camera_3d.cpp}}
//--STRIP
//#include "render_objects/sprite.h"
//--STRIP
{{FILE:sfw/render_objects/sprite.cpp}}
//--STRIP
//#include "render_objects/camera_2d.h"
//#include "core/math_funcs.h"
//#include "render_core/render_state.h"
//--STRIP
{{FILE:sfw/render_objects/camera_2d.cpp}}
//--STRIP
//#include "render_objects/mesh_instance_3d.h"
//#include "render_objects/camera_3d.h"
//--STRIP
{{FILE:sfw/render_objects/mesh_instance_3d.cpp}}
//--STRIP
//#include "render_objects/object_3d.h"
//--STRIP
{{FILE:sfw/render_objects/object_3d.cpp}}
//--STRIP
//#include "render_objects/tile_map.h"
//#include "render_objects/camera_2d.h"
//--STRIP
{{FILE:sfw/render_objects/tile_map.cpp}}
//--STRIP
//#include "render_objects/text_2d.h"
//#include "render_core/font.h"
//#include "render_core/font_material.h"
//#include "render_core/mesh.h"
//#include "render_objects/camera_2d.h"
//--STRIP
{{FILE:sfw/render_objects/text_2d.cpp}}
//--STRIP
//#include "render_objects/object_2d.h"
//--STRIP
{{FILE:sfw/render_objects/object_2d.cpp}}
//--STRIP
//#include "render_objects/mesh_instance_2d.h"
//#include "render_objects/camera_2d.h"
//--STRIP
{{FILE:sfw/render_objects/mesh_instance_2d.cpp}}

