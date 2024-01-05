

//Add the implementation unroll macros here before including sfw.h

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

#ifndef SFW_3RD_H
#define SFW_3RD_H
#include "sfw"
#endif

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
//#include "core/stime.h"
//--STRIP
{{FILE:sfw/core/stime.cpp}}

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
//#include "core/random_pcg.h"
//#include "core/stime.h"
//#include "core/error_macros.h"
//--STRIP
{{FILE:sfw/core/random_pcg.cpp}}
//--STRIP
//#include "core/vector4.h"
//#include "core/basis.h"
//--STRIP
{{FILE:sfw/core/vector4.cpp}}

//--STRIP
//===================  OBJECT SECTION  ===================
//--STRIP

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

//--STRIP
//===================  RENDER CORE SECTION  ===================
//--STRIP

{{FILE:sfw/render_core/font_data_bm_mini.inc.h}}
{{FILE:sfw/render_core/font_data_tables.inc.h}}

//--STRIP
//#include "render_core/texture.h"
//#include "core/memory.h"
//#include "render_core/window.h"
//--STRIP
{{FILE:sfw/render_core/texture.cpp}}
//--STRIP
//#include "render_core/application.h"
//#include "core/math_defs.h"
//#include "core/stime.h"
//#include "render_core/input.h"
//#include "render_core/input_map.h"
//#include "render_core/window.h"
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
//#include "window.h"
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
//#include "render_core/material.h"
//--STRIP
{{FILE:sfw/render_core/material.cpp}}
//--STRIP
//{//{FILE:sfw/render_core/primitive_meshes.cpp}}
//--STRIP

//--STRIP
//#include "render_core/image.h"
//#include "core/error_macros.h"
//#include "core/hash_map.h"
//#include "math.h"
//#include "core/memory.h"
//#include "core/vector3.h"
//#include "3rd_stb_image.h"
//--STRIP
{{FILE:sfw/render_core/image.cpp}}
//--STRIP
//#include "render_core/window.h"
//#include "render_core/3rd_glad.h"
//#include "3rd_glfw3.h"
//#include "core/error_macros.h"
//#include "core/stime.h"
//#include "core/ustring.h"
//#include "core/vector4.h"
//#include "render_core/application.h"
//#include "render_core/input.h"
//--STRIP
{{FILE:sfw/render_core/window.cpp}}
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
//#include "core/stime.h"
//#include "render_core/application.h"
//#include "render_core/input_map.h"
//#include "render_core/keyboard.h"
//#include "render_core/texture.h"
//#include "render_core/window.h"
//#include "render_core/3rd_glfw3.h"
//--STRIP
{{FILE:sfw/render_core/input.cpp}}

//--STRIP
//===================  RENDER IMMEDIATE SECTION  ===================
//--STRIP

//--STRIP
//#include "renderer.h"
//#include "render_core/color_material_2d.h"
//#include "render_core/font.h"
//#include "render_core/font_material.h"
//#include "render_core/material.h"
//#include "render_core/mesh.h"
//#include "render_core/texture.h"
//#include "render_core/texture_material_2d.h"
//#include "render_core/window.h"
//#include "render_core/render_state.h"
//--STRIP
{{FILE:sfw/render_immediate/renderer.cpp}}

//--STRIP
//===================  RENDER OBJCTS SECTION  ===================
//--STRIP

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

