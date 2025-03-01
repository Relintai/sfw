

{{FILEINLINE:tools/merger/sfw_readme.inl.h}}

// MODULES:
// CORE + OBJECT + RENDER CORE + RENDER IMMEDIATE + RENDER OBJECTS

// LICENSES:

{{FILEINLINE:tools/merger/sfw_linceses_core.inl.h}}
{{FILEINLINE:tools/merger/sfw_linceses_render_core.inl.h}}

#include <cstdio>
#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <time.h>
#include <ctime>
#include <wchar.h>
#include <cstdint>
#include <memory.h>

#if !defined(_WIN64) && !defined(_WIN32)
#include <sys/time.h>
#include <unistd.h>
#endif

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

// Note: On Windows we need to make sure that 
// GLFW includes it's needed windows headers first, as it has quite a bit of setup.
// Also windows headers can define quite a bit of stuff like far and near macros
// Wee need to make sure it's safe to undo those as soon as possible
// This means that <windows.h> cannot be included in sfw.h if rendering is enabled.
// Also since it pull in lots of defines it probably shouldn't anyway.
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
//#include "core/vector2i.h"
//#include "core/ustring.h"
//--STRIP
{{FILE:sfw/core/vector2i.cpp}}
//--STRIP
//#include "core/vector2.h"
//#include "core/vector2i.h"
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
//#include "string_builder.h"
//#include <string.h>
//--STRIP
{{FILE:sfw/core/string_builder.cpp}}

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
{{FILE:sfw/render_core/frame_buffer.cpp}}
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
//#includes own header
//--STRIP
{{FILE:sfw/render_core/colored_texture_material_2d.cpp}}

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

//===================  RENDER OBJECTS SECTION  ===================

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


//===================  GUI SECTION  ===================

// [SECTION] Forward declarations

struct ImBitVector;                 // Store 1-bit per value
struct ImRect;                      // An axis-aligned rectangle (2 points)
struct ImDrawDataBuilder;           // Helper to build a ImDrawData instance
struct ImDrawListSharedData;        // Data shared between all ImDrawList instances
struct ImGuiBoxSelectState;         // Box-selection state (currently used by multi-selection, could potentially be used by others)
struct ImGuiColorMod;               // Stacked color modifier, backup of modified data so we can restore it
struct ImGuiContext;                // Main Dear ImGui context
struct ImGuiContextHook;            // Hook for extensions like ImGuiTestEngine
struct ImGuiDataVarInfo;            // Variable information (e.g. to access style variables from an enum)
struct ImGuiDataTypeInfo;           // Type information associated to a ImGuiDataType enum
struct ImGuiGroupData;              // Stacked storage data for BeginGroup()/EndGroup()
struct ImGuiInputTextState;         // Internal state of the currently focused/edited text input box
struct ImGuiInputTextDeactivateData;// Short term storage to backup text of a deactivating InputText() while another is stealing active id
struct ImGuiLastItemData;           // Status storage for last submitted items
struct ImGuiLocEntry;               // A localization entry.
struct ImGuiMenuColumns;            // Simple column measurement, currently used for MenuItem() only
struct ImGuiMultiSelectState;       // Multi-selection persistent state (for focused selection).
struct ImGuiMultiSelectTempData;    // Multi-selection temporary state (while traversing).
struct ImGuiNavItemData;            // Result of a gamepad/keyboard directional navigation move query result
struct ImGuiMetricsConfig;          // Storage for ShowMetricsWindow() and DebugNodeXXX() functions
struct ImGuiNextWindowData;         // Storage for SetNextWindow** functions
struct ImGuiNextItemData;           // Storage for SetNextItem** functions
struct ImGuiOldColumnData;          // Storage data for a single column for legacy Columns() api
struct ImGuiOldColumns;             // Storage data for a columns set for legacy Columns() api
struct ImGuiPopupData;              // Storage for current popup stack
struct ImGuiSettingsHandler;        // Storage for one type registered in the .ini file
struct ImGuiStackSizes;             // Storage of stack sizes for debugging/asserting
struct ImGuiStyleMod;               // Stacked style modifier, backup of modified data so we can restore it
struct ImGuiTabBar;                 // Storage for a tab bar
struct ImGuiTabItem;                // Storage for a tab item (within a tab bar)
struct ImGuiTable;                  // Storage for a table
struct ImGuiTableHeaderData;        // Storage for TableAngledHeadersRow()
struct ImGuiTableColumn;            // Storage for one column of a table
struct ImGuiTableInstanceData;      // Storage for one instance of a same table
struct ImGuiTableTempData;          // Temporary storage for one table (one per table in the stack), shared between tables.
struct ImGuiTableSettings;          // Storage for a table .ini settings
struct ImGuiTableColumnsSettings;   // Storage for a column .ini settings
struct ImGuiTreeNodeStackData;      // Temporary storage for TreeNode().
struct ImGuiTypingSelectState;      // Storage for GetTypingSelectRequest()
struct ImGuiTypingSelectRequest;    // Storage for GetTypingSelectRequest() (aimed to be public)
struct ImGuiWindow;                 // Storage for one window
struct ImGuiWindowTempData;         // Temporary storage for one window (that's the data which in theory we could ditch at the end of the frame, in practice we currently keep it for each window)
struct ImGuiWindowSettings;         // Storage for a window .ini settings (we keep one of those even if the actual window wasn't instanced during this session)

// Enumerations
// Use your programming IDE "Go to definition" facility on the names of the center columns to find the actual flags/enum lists.
enum ImGuiLocKey : int;                 // -> enum ImGuiLocKey              // Enum: a localization entry for translation.
typedef int ImGuiLayoutType;            // -> enum ImGuiLayoutType_         // Enum: Horizontal or vertical

// Flags
typedef int ImGuiActivateFlags;         // -> enum ImGuiActivateFlags_      // Flags: for navigation/focus function (will be for ActivateItem() later)
typedef int ImGuiDebugLogFlags;         // -> enum ImGuiDebugLogFlags_      // Flags: for ShowDebugLogWindow(), g.DebugLogFlags
typedef int ImGuiFocusRequestFlags;     // -> enum ImGuiFocusRequestFlags_  // Flags: for FocusWindow();
typedef int ImGuiItemStatusFlags;       // -> enum ImGuiItemStatusFlags_    // Flags: for g.LastItemData.StatusFlags
typedef int ImGuiOldColumnFlags;        // -> enum ImGuiOldColumnFlags_     // Flags: for BeginColumns()
typedef int ImGuiNavHighlightFlags;     // -> enum ImGuiNavHighlightFlags_  // Flags: for RenderNavHighlight()
typedef int ImGuiNavMoveFlags;          // -> enum ImGuiNavMoveFlags_       // Flags: for navigation requests
typedef int ImGuiNextItemDataFlags;     // -> enum ImGuiNextItemDataFlags_  // Flags: for SetNextItemXXX() functions
typedef int ImGuiNextWindowDataFlags;   // -> enum ImGuiNextWindowDataFlags_// Flags: for SetNextWindowXXX() functions
typedef int ImGuiScrollFlags;           // -> enum ImGuiScrollFlags_        // Flags: for ScrollToItem() and navigation requests
typedef int ImGuiSeparatorFlags;        // -> enum ImGuiSeparatorFlags_     // Flags: for SeparatorEx()
typedef int ImGuiTextFlags;             // -> enum ImGuiTextFlags_          // Flags: for TextEx()
typedef int ImGuiTooltipFlags;          // -> enum ImGuiTooltipFlags_       // Flags: for BeginTooltipEx()
typedef int ImGuiTypingSelectFlags;     // -> enum ImGuiTypingSelectFlags_  // Flags: for GetTypingSelectRequest()
typedef int ImGuiWindowRefreshFlags;    // -> enum ImGuiWindowRefreshFlags_ // Flags: for SetNextWindowRefreshPolicy()

typedef void (*ImGuiErrorLogCallback)(void* user_data, const char* fmt, ...);


static bool     InputTextFilterCharacter(ImGuiContext* ctx, unsigned int* p_char, ImGuiInputTextFlags flags, ImGuiInputTextCallback callback, void* user_data, bool input_source_is_clipboard = false);
static int      InputTextCalcTextLenAndLineCount(const char* text_begin, const char** out_text_end);
static ImVec2   InputTextCalcTextSizeW(ImGuiContext* ctx, const ImWchar* text_begin, const ImWchar* text_end, const ImWchar** remaining = NULL, ImVec2* out_offset = NULL, bool stop_on_new_line = false);


namespace ImStb
{

#undef IMSTB_TEXTEDIT_STRING
#undef IMSTB_TEXTEDIT_CHARTYPE
#define IMSTB_TEXTEDIT_STRING             ImGuiInputTextState
#define IMSTB_TEXTEDIT_CHARTYPE           ImWchar
#define IMSTB_TEXTEDIT_GETWIDTH_NEWLINE   (-1.0f)
#define IMSTB_TEXTEDIT_UNDOSTATECOUNT     99
#define IMSTB_TEXTEDIT_UNDOCHARCOUNT      999
{{FILE:sfw/render_gui/imstb_textedit.h}}

} // namespace ImStb

//--STRIP
//#include "imgui.h"
//#include "imstb_textedit.h"
//--STRIP
{{FILE:sfw/render_gui/imgui_internal.h}}

// Wrapper for stb_textedit.h to edit text (our wrapper is for: statically sized buffer, single-line, wchar characters. InputText converts between UTF-8 and wchar)
namespace ImStb
{

static int     STB_TEXTEDIT_STRINGLEN(const ImGuiInputTextState* obj)                             { return obj->CurLenW; }
static ImWchar STB_TEXTEDIT_GETCHAR(const ImGuiInputTextState* obj, int idx)                      { IM_ASSERT(idx <= obj->CurLenW); return obj->TextW[idx]; }
static float   STB_TEXTEDIT_GETWIDTH(ImGuiInputTextState* obj, int line_start_idx, int char_idx)  { ImWchar c = obj->TextW[line_start_idx + char_idx]; if (c == '\n') return IMSTB_TEXTEDIT_GETWIDTH_NEWLINE; ImGuiContext& g = *obj->Ctx; return g.Font->GetCharAdvance(c) * g.FontScale; }
static int     STB_TEXTEDIT_KEYTOTEXT(int key)                                                    { return key >= 0x200000 ? 0 : key; }
static ImWchar STB_TEXTEDIT_NEWLINE = '\n';
static void    STB_TEXTEDIT_LAYOUTROW(StbTexteditRow* r, ImGuiInputTextState* obj, int line_start_idx)
{
    const ImWchar* text = obj->TextW.Data;
    const ImWchar* text_remaining = NULL;
    const ImVec2 size = InputTextCalcTextSizeW(obj->Ctx, text + line_start_idx, text + obj->CurLenW, &text_remaining, NULL, true);
    r->x0 = 0.0f;
    r->x1 = size.x;
    r->baseline_y_delta = size.y;
    r->ymin = 0.0f;
    r->ymax = size.y;
    r->num_chars = (int)(text_remaining - (text + line_start_idx));
}

static bool is_separator(unsigned int c)
{
    return c==',' || c==';' || c=='(' || c==')' || c=='{' || c=='}' || c=='[' || c==']' || c=='|' || c=='\n' || c=='\r' || c=='.' || c=='!' || c=='\\' || c=='/';
}

static int is_word_boundary_from_right(ImGuiInputTextState* obj, int idx)
{
    // When ImGuiInputTextFlags_Password is set, we don't want actions such as CTRL+Arrow to leak the fact that underlying data are blanks or separators.
    if ((obj->Flags & ImGuiInputTextFlags_Password) || idx <= 0)
        return 0;

    bool prev_white = ImCharIsBlankW(obj->TextW[idx - 1]);
    bool prev_separ = is_separator(obj->TextW[idx - 1]);
    bool curr_white = ImCharIsBlankW(obj->TextW[idx]);
    bool curr_separ = is_separator(obj->TextW[idx]);
    return ((prev_white || prev_separ) && !(curr_separ || curr_white)) || (curr_separ && !prev_separ);
}
static int is_word_boundary_from_left(ImGuiInputTextState* obj, int idx)
{
    if ((obj->Flags & ImGuiInputTextFlags_Password) || idx <= 0)
        return 0;

    bool prev_white = ImCharIsBlankW(obj->TextW[idx]);
    bool prev_separ = is_separator(obj->TextW[idx]);
    bool curr_white = ImCharIsBlankW(obj->TextW[idx - 1]);
    bool curr_separ = is_separator(obj->TextW[idx - 1]);
    return ((prev_white) && !(curr_separ || curr_white)) || (curr_separ && !prev_separ);
}
static int  STB_TEXTEDIT_MOVEWORDLEFT_IMPL(ImGuiInputTextState* obj, int idx)   { idx--; while (idx >= 0 && !is_word_boundary_from_right(obj, idx)) idx--; return idx < 0 ? 0 : idx; }
static int  STB_TEXTEDIT_MOVEWORDRIGHT_MAC(ImGuiInputTextState* obj, int idx)   { idx++; int len = obj->CurLenW; while (idx < len && !is_word_boundary_from_left(obj, idx)) idx++; return idx > len ? len : idx; }
static int  STB_TEXTEDIT_MOVEWORDRIGHT_WIN(ImGuiInputTextState* obj, int idx)   { idx++; int len = obj->CurLenW; while (idx < len && !is_word_boundary_from_right(obj, idx)) idx++; return idx > len ? len : idx; }
static int  STB_TEXTEDIT_MOVEWORDRIGHT_IMPL(ImGuiInputTextState* obj, int idx)  { ImGuiContext& g = *obj->Ctx; if (g.IO.ConfigMacOSXBehaviors) return STB_TEXTEDIT_MOVEWORDRIGHT_MAC(obj, idx); else return STB_TEXTEDIT_MOVEWORDRIGHT_WIN(obj, idx); }
#define STB_TEXTEDIT_MOVEWORDLEFT   STB_TEXTEDIT_MOVEWORDLEFT_IMPL  // They need to be #define for stb_textedit.h
#define STB_TEXTEDIT_MOVEWORDRIGHT  STB_TEXTEDIT_MOVEWORDRIGHT_IMPL

static void STB_TEXTEDIT_DELETECHARS(ImGuiInputTextState* obj, int pos, int n)
{
    ImWchar* dst = obj->TextW.Data + pos;

    // We maintain our buffer length in both UTF-8 and wchar formats
    obj->Edited = true;
    obj->CurLenA -= ImTextCountUtf8BytesFromStr(dst, dst + n);
    obj->CurLenW -= n;

    // Offset remaining text (FIXME-OPT: Use memmove)
    const ImWchar* src = obj->TextW.Data + pos + n;
    while (ImWchar c = *src++)
        *dst++ = c;
    *dst = '\0';
}

static bool STB_TEXTEDIT_INSERTCHARS(ImGuiInputTextState* obj, int pos, const ImWchar* new_text, int new_text_len)
{
    const bool is_resizable = (obj->Flags & ImGuiInputTextFlags_CallbackResize) != 0;
    const int text_len = obj->CurLenW;
    IM_ASSERT(pos <= text_len);

    const int new_text_len_utf8 = ImTextCountUtf8BytesFromStr(new_text, new_text + new_text_len);
    if (!is_resizable && (new_text_len_utf8 + obj->CurLenA + 1 > obj->BufCapacityA))
        return false;

    // Grow internal buffer if needed
    if (new_text_len + text_len + 1 > obj->TextW.Size)
    {
        if (!is_resizable)
            return false;
        IM_ASSERT(text_len < obj->TextW.Size);
        obj->TextW.resize(text_len + ImClamp(new_text_len * 4, 32, ImMax(256, new_text_len)) + 1);
    }

    ImWchar* text = obj->TextW.Data;
    if (pos != text_len)
        memmove(text + pos + new_text_len, text + pos, (size_t)(text_len - pos) * sizeof(ImWchar));
    memcpy(text + pos, new_text, (size_t)new_text_len * sizeof(ImWchar));

    obj->Edited = true;
    obj->CurLenW += new_text_len;
    obj->CurLenA += new_text_len_utf8;
    obj->TextW[obj->CurLenW] = '\0';

    return true;
}

// We don't use an enum so we can build even with conflicting symbols (if another user of stb_textedit.h leak their STB_TEXTEDIT_K_* symbols)
#define STB_TEXTEDIT_K_LEFT         0x200000 // keyboard input to move cursor left
#define STB_TEXTEDIT_K_RIGHT        0x200001 // keyboard input to move cursor right
#define STB_TEXTEDIT_K_UP           0x200002 // keyboard input to move cursor up
#define STB_TEXTEDIT_K_DOWN         0x200003 // keyboard input to move cursor down
#define STB_TEXTEDIT_K_LINESTART    0x200004 // keyboard input to move cursor to start of line
#define STB_TEXTEDIT_K_LINEEND      0x200005 // keyboard input to move cursor to end of line
#define STB_TEXTEDIT_K_TEXTSTART    0x200006 // keyboard input to move cursor to start of text
#define STB_TEXTEDIT_K_TEXTEND      0x200007 // keyboard input to move cursor to end of text
#define STB_TEXTEDIT_K_DELETE       0x200008 // keyboard input to delete selection or character under cursor
#define STB_TEXTEDIT_K_BACKSPACE    0x200009 // keyboard input to delete selection or character left of cursor
#define STB_TEXTEDIT_K_UNDO         0x20000A // keyboard input to perform undo
#define STB_TEXTEDIT_K_REDO         0x20000B // keyboard input to perform redo
#define STB_TEXTEDIT_K_WORDLEFT     0x20000C // keyboard input to move cursor left one word
#define STB_TEXTEDIT_K_WORDRIGHT    0x20000D // keyboard input to move cursor right one word
#define STB_TEXTEDIT_K_PGUP         0x20000E // keyboard input to move cursor up a page
#define STB_TEXTEDIT_K_PGDOWN       0x20000F // keyboard input to move cursor down a page
#define STB_TEXTEDIT_K_SHIFT        0x400000

#undef IMSTB_TEXTEDIT_STRING
#undef IMSTB_TEXTEDIT_CHARTYPE
#define IMSTB_TEXTEDIT_STRING             ImGuiInputTextState
#define IMSTB_TEXTEDIT_CHARTYPE           ImWchar
#define IMSTB_TEXTEDIT_GETWIDTH_NEWLINE   (-1.0f)
#define IMSTB_TEXTEDIT_UNDOSTATECOUNT     99
#define IMSTB_TEXTEDIT_UNDOCHARCOUNT      999

#define IMSTB_TEXTEDIT_IMPLEMENTATION
#define IMSTB_TEXTEDIT_memmove memmove

{{FILE:sfw/render_gui/imstb_textedit.h}}

// stb_textedit internally allows for a single undo record to do addition and deletion, but somehow, calling
// the stb_textedit_paste() function creates two separate records, so we perform it manually. (FIXME: Report to nothings/stb?)
static void stb_textedit_replace(ImGuiInputTextState* str, STB_TexteditState* state, const IMSTB_TEXTEDIT_CHARTYPE* text, int text_len)
{
    stb_text_makeundo_replace(str, state, 0, str->CurLenW, text_len);
    ImStb::STB_TEXTEDIT_DELETECHARS(str, 0, str->CurLenW);
    state->cursor = state->select_start = state->select_end = 0;
    if (text_len <= 0)
        return;
    if (ImStb::STB_TEXTEDIT_INSERTCHARS(str, 0, text, text_len))
    {
        state->cursor = state->select_start = state->select_end = text_len;
        state->has_preferred_x = 0;
        return;
    }
    IM_ASSERT(0); // Failed to insert character, normally shouldn't happen because of how we currently use stb_textedit_replace()
}

} // namespace ImStb

//--STRIP
//#include "imgui.h"
//#include "imgui_internal.h"
//#include <stdint.h>     // intptr_t
//#include "imstb_textedit.h"
//--STRIP
{{FILE:sfw/render_gui/imgui_widgets.cpp}}


//--STRIP
//#include "imgui.h"
//#include "imgui_internal.h"
//--STRIP
{{FILE:sfw/render_gui/imgui_tables.cpp}}

//#define STBRP_STATIC
//#define STBRP_ASSERT(x)     do { IM_ASSERT(x); } while (0)
//#define STBRP_SORT          ImQsort
//#define STB_RECT_PACK_IMPLEMENTATION
//{{F I L E:sfw/render_gui/imstb_rectpack.h}}

//--STRIP
//#include "imgui.h"
//#include "imgui_internal.h"
//#include <stdio.h>      // vsnprintf, sscanf, printf
//#include "imstb_rectpack.h"
//#include "imstb_truetype.h"
//--STRIP
{{FILE:sfw/render_gui/imgui_draw.cpp}}

//--STRIP
//#include "imgui.h"      // IMGUI_IMPL_API
//--STRIP
{{FILE:sfw/render_gui/imgui_impl_glfw.h}}

//--STRIP
//#include "imgui.h"
//#include "imgui_impl_glfw.h"
//#if defined(_WIN64) || defined(_WIN32)
//#define WIN32_LEAN_AND_MEAN
//#include <windows.h>
//#endif
//#include "render_core/3rd_glfw3.h"
//--STRIP
{{FILE:sfw/render_gui/imgui_impl_glfw.cpp}}

//--STRIP
//#include "imgui.h"      // IMGUI_IMPL_API
//--STRIP
{{FILE:sfw/render_gui/imgui_impl_opengl3.h}}

//--STRIP
//#include "imgui.h"
//#ifndef IMGUI_DISABLE
//#include "imgui_internal.h"
//#endif
//--STRIP
{{FILE:sfw/render_gui/imgui.cpp}}

//--STRIP
//#include "imgui_impl_opengl3_loader.h"
//--STRIP
#define IMGUI_IMPL_OPENGL_LOADER_CUSTOM
//#define IMGL3W_IMPL
//{{F I LE:sfw/render_gui/imgui_impl_opengl3_loader.h}}

//--STRIP
//#include "imgui.h"
//#include "imgui_impl_opengl3.h"
//#include <stdio.h>
//#include <stdint.h>     // intptr_t
//#include "imgui_impl_opengl3_loader.h"
//--STRIP
{{FILE:sfw/render_gui/imgui_impl_opengl3.cpp}}

//--STRIP
//#include "gui.h"
//#include "render_core/app_window.h"
//#include "imgui.h"
//#include "imgui_impl_glfw.h"
//#include "imgui_impl_opengl3.h"
//#include <stdio.h>
//--STRIP
{{FILE:sfw/render_gui/gui.cpp}}

