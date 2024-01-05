#ifndef SFW_H
#define SFW_H

// https://github.com/Relintai/sfw

/*
Copyright (c) 2023-present Péter Magyar.

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

// TODO gather all licenses to here

#include <float.h>
#include <math.h>
#include <string.h>
#include <stddef.h>

//no includes
{{FILE:sfw/core/typedefs.h}}
//no includes
{{FILE:sfw/core/int_types.h}}
//no includes
{{FILE:sfw/core/math_defs.h}}
//no includes
{{FILE:sfw/core/error_list.h}}
//#include "core/logger.h"
//#include "core/typedefs.h"
{{FILE:sfw/core/error_macros.h}}

//#include "core/error_macros.h"
//#include "core/math_defs.h"
//#include "core/random_pcg.h"
//#include "core/typedefs.h"
//#include "core/pcg.h"
{{FILE:sfw/core/math_funcs.h}}

//#include "core/typedefs.h"
{{FILE:sfw/core/safe_refcount.h}}
//#include "core/mutex.h"
{{FILE:sfw/core/thread_safe.h}}
//#include "core/error_list.h"
{{FILE:sfw/core/rw_lock.h}}
//#include "core/error_list.h"
//#include "core/typedefs.h"
{{FILE:sfw/core/mutex.h}}
//#include "core/typedefs.h"
{{FILE:sfw/core/spin_lock.h}}

//#include "core/error_macros.h"
//#include "core/safe_refcount.h"
{{FILE:sfw/core/memory.h}}

//#include "core/aabb.h"
//#include "core/math_defs.h"
//#include "core/math_funcs.h"
//#include "core/rect2.h"
//#include "core/rect2i.h"
//#include "core/vector2.h"
//#include "core/vector2i.h"
//#include "core/vector3.h"
//#include "core/vector3i.h"
//#include "core/vector4.h"
//#include "core/vector4i.h"
//#include "core/string_name.h"
//#include "core/ustring.h"
//#include "core/typedefs.h"
{{FILE:sfw/core/hashfuncs.h}}

//#include "core/int_types.h"
{{FILE:sfw/core/stime.h}}
//no includes
{{FILE:sfw/core/logger.h}}

//#include "core/hashfuncs.h"
//#include "core/typedefs.h"
{{FILE:sfw/core/pair.h}}
//#include "core/error_list.h"
//#include "core/error_macros.h"
//#include "core/memory.h"
//#include "core/safe_refcount.h"
{{FILE:sfw/core/cowdata.h}}
//#include "core/error_macros.h"
//#include "core/typedefs.h"
{{FILE:sfw/core/sort_array.h}}
//#include "cowdata.h"
//#include "core/typedefs.h"
{{FILE:sfw/core/vmap.h}}
//#include "core/error_macros.h"
//#include "core/memory.h"
{{FILE:sfw/core/rb_map.h}}
//#include "core/hashfuncs.h"
//#include "core/list.h"
//#include "core/error_macros.h"
//#include "core/math_funcs.h"
//#include "core/memory.h"
//#include "core/ustring.h"
{{FILE:sfw/core/og_hash_map.h}}
//#include "core/vector.h"
//#include "core/typedefs.h"
{{FILE:sfw/core/vset.h}}
//#include "cowdata.h"
//#include "core/sort_array.h"
//#include "core/error_macros.h"
//#include "core/memory.h"
{{FILE:sfw/core/vector.h}}
//#include "core/hashfuncs.h"
//#include "paged_allocator.h"
//#include "pair.h"
//#include "core/math_funcs.h"
//#include "core/memory.h"
//#include "list.h"
{{FILE:sfw/core/hash_map.h}}
//#include "core/vector.h"
{{FILE:sfw/core/ring_buffer.h}}
//#include "core/memory.h"
//#include "core/mutex.h"
//#include "pool_allocator.h"
//#include "rw_lock.h"
//#include "core/safe_refcount.h"
//#include "core/ustring.h"
{{FILE:sfw/core/pool_vector.h}}
//#include "core/memory.h"
//#include "spin_lock.h"
//#include "core/typedefs.h"
{{FILE:sfw/core/paged_allocator.h}}
//#include "core/typedefs.h"
{{FILE:sfw/core/pool_allocator.h}}
//#include "core/sort_array.h"
//#include "core/error_macros.h"
//#include "core/memory.h"
{{FILE:sfw/core/list.h}}
//#include "core/hash_map.h"
//#include "core/hashfuncs.h"
//#include "core/math_funcs.h"
//#include "core/memory.h"
{{FILE:sfw/core/hash_set.h}}
//#include "core/pool_vector.h"
//#include "core/sort_array.h"
//#include "core/vector.h"
//#include "core/error_macros.h"
//#include "core/memory.h"
{{FILE:sfw/core/tight_local_vector.h}}
//#include "core/memory.h"
//#include "core/typedefs.h"
{{FILE:sfw/core/rb_set.h}}
//#include "core/pool_vector.h"
//#include "core/sort_array.h"
//#include "core/vector.h"
//#include "core/error_macros.h"
//#include "core/memory.h"
{{FILE:sfw/core/local_vector.h}}
//#include "core/list.h"
//#include "core/og_hash_map.h"
//#include "core/pair.h"
{{FILE:sfw/core/ordered_hash_map.h}}


//#include "core/mutex.h"
//#include "core/safe_refcount.h"
//#include "core/ustring.h"
{{FILE:sfw/core/string_name.h}}

//#include "core/typedefs.h"
{{FILE:sfw/core/char_range.inc}}
//#include "core/typedefs.h"
//#include "core/char_range.inc"
{{FILE:sfw/core/char_utils.h}}
//#include "cowdata.h"
//#include "core/vector.h"
//#include "char_utils.h"
//#include "core/typedefs.h"
{{FILE:sfw/core/ustring.h}}

//#include "core/math_funcs.h"
//#include "core/ustring.h"
{{FILE:sfw/core/color.h}}

//#include "core/math_funcs.h"
//#include "core/ustring.h"
{{FILE:sfw/core/vector3.h}}

//#include "core/vector3.h"
{{FILE:sfw/core/plane.h}}
//#include "core/math_defs.h"
//#include "core/plane.h"
//#include "core/vector3.h"
{{FILE:sfw/core/aabb.h}}


//#include "core/typedefs.h"
{{FILE:sfw/core/pcg.h}}

//#include "core/math_defs.h"
//#include "core/pcg.h"
{{FILE:sfw/core/random_pcg.h}}

//#include "core/pool_vector.h"
//#include "core/rect2.h" // also includes vector2, math_funcs, and ustring
//#include "core/rect2i.h" // also includes vector2i, math_funcs, and ustring
{{FILE:sfw/core/transform_2d.h}}
//#include "core/math_funcs.h"
//#include "core/error_macros.h"
{{FILE:sfw/core/vector2.h}}
//#include "core/error_macros.h"
//#include "core/math_funcs.h"
//#include "core/vector2.h"
{{FILE:sfw/core/vector2i.h}}

//#include "core/math_defs.h"
//#include "core/math_funcs.h"
//#include "core/vector3.h"
//#include "core/ustring.h"
{{FILE:sfw/core/quaternion.h}}


//#include "core/vector2.h" // also includes math_funcs and ustring
//#include "core/vector2i.h"
{{FILE:sfw/core/rect2.h}}
//#include "core/aabb.h"
//#include "core/plane.h"
//#include "core/transform.h"
//#include "core/vector3.h"
{{FILE:sfw/core/face3.h}}
{{FILE:sfw/core/vector4.h}}
//#include "core/vector2i.h" // also includes math_funcs and ustring
{{FILE:sfw/core/rect2i.h}}
//#include "core/vector.h"
//#include "core/math_defs.h"
//#include "core/vector3.h"
//#include "core/math_defs.h"
//#include "core/math_funcs.h"
//#include "core/ustring.h"
//#include "core/vector4.h"
{{FILE:sfw/core/projection.h}}

//#include "core/error_macros.h"
//#include "core/math_funcs.h"
{{FILE:sfw/core/vector3i.h}}
//#include "core/error_macros.h"
//#include "core/math_funcs.h"
{{FILE:sfw/core/vector4i.h}}
//#include "core/quaternion.h"
//#include "core/vector3.h"
//#include "core/vector3i.h"
{{FILE:sfw/core/basis.h}}
//#include "core/aabb.h"
//#include "core/basis.h"
//#include "core/plane.h"
//#include "core/vector3i.h"
//#include "core/pool_vector.h"
{{FILE:sfw/core/transform.h}}

//#include "core/hash_map.h"
//#include "core/rw_lock.h"
//#include "core/string_name.h"
//#include "core/ustring.h"
//#include "core/vector.h"
//#include "object/object_id.h"
//#include "object/variant.h"

//#include "object/dictionary.h"
{{FILE:sfw/object/object.h}}
//#include "core/typedefs.h"
{{FILE:sfw/object/ref_ptr.h}}
//#include "core/aabb.h"
//#include "core/basis.h"
//#include "core/color.h"
//#include "core/face3.h"
//#include "core/plane.h"
//#include "core/pool_vector.h"
//#include "core/projection.h"
//#include "core/quaternion.h"
//#include "core/transform.h"
//#include "core/transform_2d.h"
//#include "core/ustring.h"
//#include "core/vector3.h"
//#include "core/vector3i.h"
//#include "core/vector4.h"
//#include "core/vector4i.h"
//#include "object/array.h"
//#include "object/dictionary.h"
//#include "object/ref_ptr.h"
//#include "object/object_id.h"
{{FILE:sfw/object/variant.h}}
//#include "core/list.h"
//#include "core/ustring.h"
//#include "object/array.h"
{{FILE:sfw/object/dictionary.h}}
//#include "object/reference.h"
//#include "psignal.h"
{{FILE:sfw/object/resource.h}}
//#include "core/int_types.h"
{{FILE:sfw/object/object_id.h}}
//#include "core/memory.h"
//#include "core/typedefs.h"
{{FILE:sfw/object/object_rc.h}}
//#include "core/string_name.h"
{{FILE:sfw/object/core_string_names.h}}
//#include "core/memory.h"
//#include "core/safe_refcount.h"
//#include "object/object.h"
//#include "object/ref_ptr.h"
{{FILE:sfw/object/reference.h}}
//#include "core/vector.h"
//#include "core/ustring.h"
//#include "object/variant.h"
//#include "object/reference.h"
{{FILE:sfw/object/psignal.h}}
//#include "core/typedefs.h"
{{FILE:sfw/object/array.h}}


//#include "core/projection.h"
//#include "core/transform.h"
//#include "core/vector3.h"
//#include "core/transform_2d.h"
//#include "core/vector2.h"
{{FILE:sfw/render_core/render_state.h}}
//#include "core/color.h"
//#include "core/rect2.h"
//#include "core/rect2i.h"
//#include "object/reference.h"
//#include "core/vector.h"
//#include "core/vector2i.h"
{{FILE:sfw/render_core/image.h}}
//#include "core/vector.h"
//#include "core/int_types.h"
//#include "core/color.h"
//#include "object/resource.h"
//#include "render_core/3rd_glad.h"
{{FILE:sfw/render_core/mesh.h}}
//#include "object/resource.h"
{{FILE:sfw/render_core/shortcut.h}}
//#include "object/reference.h"
//#include "render_core/input_event.h"
{{FILE:sfw/render_core/scene.h}}
//#include "core/projection.h"
//#include "core/transform.h"
//#include "core/transform_2d.h"
//#include "object/reference.h"
//#include "render_core/shader.h"
{{FILE:sfw/render_core/material.h}}
//#include "render_core/material.h"
//#include "render_core/render_state.h"
{{FILE:sfw/render_core/color_material.h}}
//#include "core/transform_2d.h"
//#include "core/typedefs.h"
//#include "core/ustring.h"
//#include "object/resource.h"
{{FILE:sfw/render_core/input_event.h}}
//#include "render_core/material.h"
//#include "render_core/texture.h"
//#include "render_core/render_state.h"
{{FILE:sfw/render_core/color_material_2d.h}}
//#include "core/vector2i.h"
//#include "object/resource.h"
//#include "render_core/3rd_glad.h"
//#include "render_core/image.h"
{{FILE:sfw/render_core/texture.h}}
//#include "render_core/material.h"
//#include "render_core/texture.h"
//#include "render_core/render_state.h"
{{FILE:sfw/render_core/texture_material_2d.h}}
//#include "core/vector2i.h"
//#include "object/object.h"
//#include "core/rb_map.h"
//#include "core/rb_set.h"
//#include "core/thread_safe.h"
//#include "object/psignal.h"
//#include "object/reference.h"
//#include "render_core/input_event.h"
{{FILE:sfw/render_core/input.h}}
//#include "render_core/3rd_glad.h"
//#include "core/hash_map.h"
{{FILE:sfw/render_core/shader.h}}
//#include "render_core/input_event.h"
//#include "object/object.h"
//#include "core/rb_map.h"
{{FILE:sfw/render_core/input_map.h}}
//#include "render_core/material.h"
//#include "render_core/texture.h"
//#include "render_core/render_state.h"
{{FILE:sfw/render_core/transparent_texture_material.h}}
//#include "core/ustring.h"
{{FILE:sfw/render_core/keyboard.h}}
//{//{//FILE:sfw/render_core/primitive_meshes.h}}
//#include "core/color.h"
//#include "core/ustring.h"
//#include "object/resource.h"
//#include "font_material.h"
{{FILE:sfw/render_core/font.h}}
//#include "render_core/material.h"
//#include "render_core/texture.h"
//#include "render_core/render_state.h"
{{FILE:sfw/render_core/texture_material.h}}
//#include "render_core/material.h"
//#include "core/color.h"
//#include "render_core/render_state.h"
{{FILE:sfw/render_core/colored_material.h}}
//#include "core/int_types.h"
//#include "object/object.h"
//#include "object/reference.h"
//#include "render_core/scene.h"
{{FILE:sfw/render_core/application.h}}
//#include "render_core/mesh.h"
{{FILE:sfw/render_core/mesh_utils.h}}
//#include "core/color.h"
//#include "core/int_types.h"
//#include "core/vector2.h"
{{FILE:sfw/render_core/window.h}}
//#include "render_core/material.h"
//#include "render_core/texture.h"
//#include "render_core/render_state.h"
{{FILE:sfw/render_core/font_material.h}}


//#include "core/color.h"
//#include "core/rect2.h"
//#include "core/transform.h"
//#include "core/transform_2d.h"
//#include "core/vector2i.h"
//#include "object/object.h"
//#include "object/reference.h"
{{FILE:sfw/render_immediate/renderer.h}}


//#include "render_objects/object_2d.h"
//#include "core/transform_2d.h"
//#include "render_objects/mesh_instance_2d.h"
{{FILE:sfw/render_objects/sprite.h}}
//#include "core/vector.h"
//#include "render_objects/object_3d.h"
//#include "render_core/material.h"
//#include "render_core/mesh.h"
//#include "core/transform.h"
{{FILE:sfw/render_objects/mesh_instance_3d.h}}
//#include "render_core/3rd_glad.h"
//#include "render_objects/object_2d.h"
//#include "core/transform.h"
//#include "core/transform_2d.h"
//#include "core/vector2.h"
{{FILE:sfw/render_objects/camera_2d.h}}
//#include "core/color.h"
//#include "core/ustring.h"
//#include "core/vector2.h"
//#include "object/reference.h"
//#include "object_2d.h"
{{FILE:sfw/render_objects/text_2d.h}}
//#include "render_objects/object_2d.h"
//#include "render_core/mesh.h"
//#include "render_core/material.h"
{{FILE:sfw/render_objects/tile_map.h}}
//#include "object/object.h"
//#include "core/transform_2d.h"
{{FILE:sfw/render_objects/object_2d.h}}
//#include "render_objects/object_3d.h"
//#include "render_core/3rd_glad.h"
//#include "core/projection.h"
//#include "core/transform.h"
//#include "core/vector3.h"
{{FILE:sfw/render_objects/camera_3d.h}}
//#include "object/object.h"
//#include "core/transform.h"
{{FILE:sfw/render_objects/object_3d.h}}
//#include "core/vector.h"
//#include "render_core/material.h"
//#include "render_core/mesh.h"
//#include "core/transform.h"
{{FILE:sfw/render_objects/mesh_instance_2d.h}}



// expose glfw/glad apis
#if __EMSCRIPTEN__
    #include <GL/glew.h>
    #include <GLFW/glfw3.h>
    #include <emscripten.h>
    #include <emscripten/html5.h>
    #define gladLoadGL(func) (glewExperimental = true, glewInit() == GLEW_OK) ///-
#else
    #if is(win32) /*&& is(tcc)*/ // && ENABLE_DLL
    #ifdef GLAD_API_CALL
    #undef GLAD_API_CALL
    #endif
    #define GLAD_API_CALL extern API ///-
    #endif
    #ifndef GLAD_GL_H_
    #include "sfw"
    #endif
#endif

#endif
