

{{FILEINLINE:tools/merger/sfw_readme.inl.h}}
{{FILEINLINE:tools/merger/sfw_linceses.inl.h}}

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
#include "sfw.h"
#endif

#ifndef SFW_3RD_IMPL
#define SFW_3RD_IMPL

#if defined(__linux__)
//typedef XID Font;
#define Font The_Font_I_dont_care
#endif

#include "sfw_3rd.h"

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

#endif

//===================  CORE SECTION  ===================

{{FILE:sfwl/core/ucaps.h}}

//--STRIP
//#include "core/mutex.h"
//--STRIP
{{FILE:sfwl/core/mutex.cpp}}
//--STRIP
//#if defined(DEBUG_ENABLED) && !defined(NO_THREADS)
//#include "core/safe_refcount.h"
//#include "core/error/error_macros.h"
//--STRIP
{{FILE:sfwl/core/safe_refcount.cpp}}

//--STRIP
//#include "core/stime.h"
//--STRIP
{{FILE:sfwl/core/stime.cpp}}

//--STRIP
//#include "core/memory.h"
//#include "core/error_macros.h"
//#include "core/safe_refcount.h"
//--STRIP
{{FILE:sfwl/core/memory.cpp}}
//--STRIP
//{//{//FILE:sfwl/core/old/directory.cpp}}
//--STRIP

//--STRIP
//#include "core/pool_vector.h"
//--STRIP
{{FILE:sfwl/core/pool_vector.cpp}}
//--STRIP
//#include "pool_allocator.h"
//#include "core/error_macros.h"
//#include "core/memory.h"
//--STRIP
{{FILE:sfwl/core/pool_allocator.cpp}}

//--STRIP
//#include "core/random_pcg.h"
//#include "core/stime.h"
//#include "core/error_macros.h"
//--STRIP
{{FILE:sfwl/core/random_pcg.cpp}}

//--STRIP
//#include "core/math_funcs.h"
//#include "core/error_macros.h"
//--STRIP
{{FILE:sfwl/core/math_funcs.cpp}}

//--STRIP
//#include "core/ustring.h"
//#include "core/color.h"
//#include "core/math_funcs.h"
//#include "core/memory.h"
//#include "ucaps.h"
//--STRIP
{{FILE:sfwl/core/ustring.cpp}}
//--STRIP
//#include "core/logger.h"
//#include "core/ustring.h"
//--STRIP
{{FILE:sfwl/core/logger.cpp}}
//--STRIP
//#include "core/string_name.h"
//--STRIP
{{FILE:sfwl/core/string_name.cpp}}

//--STRIP
//#include "core/aabb.h"
//--STRIP
{{FILE:sfwl/core/aabb.cpp}}
//--STRIP
//#include "core/vector3i.h"
//#include "core/vector3.h"
//#include "core/ustring.h"
//--STRIP
{{FILE:sfwl/core/vector3i.cpp}}
//--STRIP
//#include "core/transform_2d.h"
//--STRIP
{{FILE:sfwl/core/transform_2d.cpp}}
//--STRIP
//#include "core/projection.h"
//#include "core/aabb.h"
//#include "core/math_funcs.h"
//#include "core/plane.h"
//#include "core/rect2.h"
//#include "core/transform.h"
//--STRIP
{{FILE:sfwl/core/projection.cpp}}
//--STRIP
//#include "core/vector3.h"
//#include "core/basis.h"
//--STRIP
{{FILE:sfwl/core/vector3.cpp}}
//--STRIP
//#include "core/pcg.h"
//--STRIP
{{FILE:sfwl/core/pcg.cpp}}
//--STRIP
//#include "core/vector2.h"
//#include "core/ustring.h"
//--STRIP
{{FILE:sfwl/core/vector2.cpp}}
//--STRIP
//#include "core/basis.h"
//#include "core/math_funcs.h"
//--STRIP
{{FILE:sfwl/core/basis.cpp}}
//--STRIP
//#include "face3.h"
//--STRIP
{{FILE:sfwl/core/face3.cpp}}
//--STRIP
//#include "core/vector4i.h"
//#include "core/vector4.h"
//#include "core/ustring.h"
//--STRIP
{{FILE:sfwl/core/vector4i.cpp}}
//--STRIP
//#include "core/transform.h"
//#include "core/math_funcs.h"
//--STRIP
{{FILE:sfwl/core/transform.cpp}}
//--STRIP
//#include "core/color.h"
//#include "core/math_funcs.h"
//--STRIP
{{FILE:sfwl/core/color.cpp}}
//--STRIP
//#include "core/quaternion.h"
//#include "core/basis.h"
//--STRIP
{{FILE:sfwl/core/quaternion.cpp}}
//--STRIP
//#include "core/plane.h"
//#include "core/math_funcs.h"
//--STRIP
{{FILE:sfwl/core/plane.cpp}}
//--STRIP
//#include "core/vector2i.h"
//#include "core/ustring.h"
//--STRIP
{{FILE:sfwl/core/vector2i.cpp}}
//--STRIP
//#include "core/transform_2d.h" // Includes rect2.h but Rect2 needs Transform2D
//#include "core/rect2i.h"
//--STRIP
{{FILE:sfwl/core/rect2.cpp}}
//--STRIP
//#include "core/transform_2d.h" // Includes rect2.h but Rect2 needs Transform2D
//--STRIP
{{FILE:sfwl/core/rect2i.cpp}}
//--STRIP
//#include "core/vector4.h"
//#include "core/basis.h"
//--STRIP
{{FILE:sfwl/core/vector4.cpp}}

//--STRIP
//#include "file_access.h"
//--STRIP
{{FILE:sfwl/core/file_access.cpp}}

{{FILE:sfwl/core/3rd_tinydir.h}}

//--STRIP
//#include "dir_access.h"
//#include "3rd_tinydir.h"
//--STRIP
{{FILE:sfwl/core/dir_access.cpp}}

//--STRIP
//#include "core/pool_vector.h"
//#include "core/string_name.h"
//--STRIP
{{FILE:sfwl/core/sfw_core.cpp}}


//===================  OBJECT SECTION  ===================

//--STRIP
//#include "resource.h"
//--STRIP
{{FILE:sfwl/object/resource.cpp}}
//--STRIP
//#include "object/reference.h"
//--STRIP
{{FILE:sfwl/object/reference.cpp}}
//--STRIP
//#include "object/object.h"
//#include "core/error_macros.h"
//#include "core/logger.h"
//#include "object/core_string_names.h"
//#include "object/object_rc.h"
//--STRIP
{{FILE:sfwl/object/object.cpp}}
//--STRIP
//#include "ref_ptr.h"
//#include "object/reference.h"
//#include "object/resource.h"
//--STRIP
{{FILE:sfwl/object/ref_ptr.cpp}}
//--STRIP
//#include "core_string_names.h"
//--STRIP
{{FILE:sfwl/object/core_string_names.cpp}}
//--STRIP
//#include "dictionary.h"
//#include "core/ordered_hash_map.h"
//#include "core/safe_refcount.h"
//#include "object/variant.h"
//--STRIP
{{FILE:sfwl/object/dictionary.cpp}}
//--STRIP
//#include "array.h"
//#include "core/hashfuncs.h"
//#include "core/vector.h"
//#include "object/object.h"
//#include "object/variant.h"
//#include "core/ustring.h"
//--STRIP
{{FILE:sfwl/object/array.cpp}}
//--STRIP
//#include "psignal.h"
//--STRIP
{{FILE:sfwl/object/psignal.cpp}}
//--STRIP
//#include "variant.h"
//#include "core/math_funcs.h"
//#include "object/core_string_names.h"
//#include "object/object.h"
//#include "object/object_rc.h"
//#include "object/resource.h"
//--STRIP
{{FILE:sfwl/object/variant.cpp}}
//--STRIP
//#include "variant.h"
//#include "object/core_string_names.h"
//#include "object/object.h"
//#include "object/object_rc.h"
//#include "object/resource.h"
//--STRIP
{{FILE:sfwl/object/variant_op.cpp}}
