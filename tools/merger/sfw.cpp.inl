

//Add the implementation unroll macros here before including sfw.h

#include "sfw.h"

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


{{FILE:sfw/core/ucaps.h}}

#include "core/mutex.h"
{{FILE:sfw/core/mutex.cpp}}
//#if defined(DEBUG_ENABLED) && !defined(NO_THREADS)
#include "core/safe_refcount.h"
#include "core/error/error_macros.h"
{{FILE:sfw/core/safe_refcount.cpp}}

#include "core/stime.h"
{{FILE:sfw/core/stime.cpp}}

#include "core/memory.h"
#include "core/error_macros.h"
#include "core/safe_refcount.h"
{{FILE:sfw/core/memory.cpp}}
//{//{//FILE:sfw/core/old/directory.cpp}}

#include "core/pool_vector.h"
{{FILE:sfw/core/pool_vector.cpp}}
#include "pool_allocator.h"
#include "core/error_macros.h"
#include "core/memory.h"
{{FILE:sfw/core/pool_allocator.cpp}}

#include "core/math_funcs.h"
#include "core/error_macros.h"
{{FILE:sfw/core/math_funcs.cpp}}

#include "core/ustring.h"

#include "core/color.h"
#include "core/math_funcs.h"
#include "core/memory.h"
#include "ucaps.h"
{{FILE:sfw/core/ustring.cpp}}
#include "core/logger.h"
#include "core/ustring.h"
{{FILE:sfw/core/logger.cpp}}
#include "core/string_name.h"
{{FILE:sfw/core/string_name.cpp}}

//#include "core/aabb.h"
{{FILE:sfw/core/aabb.cpp}}
#include "core/vector3i.h"
#include "core/vector3.h"
#include "core/ustring.h"
{{FILE:sfw/core/vector3i.cpp}}
#include "core/transform_2d.h"
{{FILE:sfw/core/transform_2d.cpp}}
#include "core/projection.h"
#include "core/aabb.h"
#include "core/math_funcs.h"
#include "core/plane.h"
#include "core/rect2.h"
#include "core/transform.h"
{{FILE:sfw/core/projection.cpp}}
#include "core/vector3.h"
#include "core/basis.h"
{{FILE:sfw/core/vector3.cpp}}
#include "core/pcg.h"
{{FILE:sfw/core/pcg.cpp}}
#include "core/vector2.h"
#include "core/ustring.h"
{{FILE:sfw/core/vector2.cpp}}
#include "core/basis.h"
#include "core/math_funcs.h"
{{FILE:sfw/core/basis.cpp}}
#include "face3.h"
{{FILE:sfw/core/face3.cpp}}
#include "core/vector4i.h"
#include "core/vector4.h"
#include "core/ustring.h"
{{FILE:sfw/core/vector4i.cpp}}
#include "core/transform.h"
#include "core/math_funcs.h"
{{FILE:sfw/core/transform.cpp}}
#include "core/color.h"
#include "core/math_funcs.h"
{{FILE:sfw/core/color.cpp}}
#include "core/quaternion.h"
#include "core/basis.h"
{{FILE:sfw/core/quaternion.cpp}}
#include "core/plane.h"
#include "core/math_funcs.h"
{{FILE:sfw/core/plane.cpp}}
#include "core/vector2i.h"
#include "core/ustring.h"
{{FILE:sfw/core/vector2i.cpp}}
#include "core/transform_2d.h" // Includes rect2.h but Rect2 needs Transform2D
#include "core/rect2i.h"
{{FILE:sfw/core/rect2.cpp}}
#include "core/transform_2d.h" // Includes rect2.h but Rect2 needs Transform2D
{{FILE:sfw/core/rect2i.cpp}}
#include "core/random_pcg.h"
#include "core/stime.h"
#include "core/error_macros.h"
{{FILE:sfw/core/random_pcg.cpp}}
#include "core/vector4.h"
#include "core/basis.h"
{{FILE:sfw/core/vector4.cpp}}

#include "resource.h"
{{FILE:sfw/object/resource.cpp}}
#include "object/reference.h"
{{FILE:sfw/object/reference.cpp}}
#include "object/object.h"
#include "core/error_macros.h"
#include "core/logger.h"
#include "object/core_string_names.h"
#include "object/object_rc.h"
{{FILE:sfw/object/object.cpp}}
#include "ref_ptr.h"
#include "object/reference.h"
#include "object/resource.h"
{{FILE:sfw/object/ref_ptr.cpp}}
#include "core_string_names.h"
{{FILE:sfw/object/core_string_names.cpp}}
#include "dictionary.h"
#include "core/ordered_hash_map.h"
#include "core/safe_refcount.h"
#include "object/variant.h"
{{FILE:sfw/object/dictionary.cpp}}
#include "array.h"
#include "core/hashfuncs.h"
#include "core/vector.h"
#include "object/object.h"
#include "object/variant.h"
#include "core/ustring.h"
{{FILE:sfw/object/array.cpp}}
#include "psignal.h"
{{FILE:sfw/object/psignal.cpp}}
#include "variant.h"
#include "core/math_funcs.h"
#include "object/core_string_names.h"
#include "object/object.h"
#include "object/object_rc.h"
#include "object/resource.h"
{{FILE:sfw/object/variant.cpp}}
#include "variant.h"
#include "object/core_string_names.h"
#include "object/object.h"
#include "object/object_rc.h"
#include "object/resource.h"
{{FILE:sfw/object/variant_op.cpp}}

{{FILE:sfw/render_core/font_data_bm_mini.inc.h}}
{{FILE:sfw/render_core/font_data_tables.inc.h}}

#include "render_core/texture.h"
#include "core/memory.h"
#include "render_core/window.h"
{{FILE:sfw/render_core/texture.cpp}}
#include "render_core/application.h"
#include "core/math_defs.h"
#include "core/stime.h"
#include "render_core/input.h"
#include "render_core/input_map.h"
#include "render_core/window.h"
#include "core/pool_vector.h"
#include "core/string_name.h"
#include "object/core_string_names.h"
{{FILE:sfw/render_core/application.cpp}}
#include "render_core/shader.h"
{{FILE:sfw/render_core/shader.cpp}}
#include "input_event.h"
#include "render_core/input_map.h"
#include "render_core/keyboard.h"
#include "render_core/shortcut.h"
{{FILE:sfw/render_core/input_event.cpp}}
#include "render_core/mesh.h"
#include "render_core/shader.h"
{{FILE:sfw/render_core/mesh.cpp}}
#include "font.h"
#include "window.h"
#include "3rd_glad.h"
#include "3rd_stb_truetype.h"
#include "font_data_bm_mini.inc.h"
#include "font_data_tables.inc.h"
#include "render_core/image.h"
#include "render_core/mesh.h"
#include "render_core/texture.h"
{{FILE:sfw/render_core/font.cpp}}
#include "render_core/render_state.h"
{{FILE:sfw/render_core/render_state.cpp}}
#include "render_core/mesh_utils.h"
{{FILE:sfw/render_core/mesh_utils.cpp}}
#include "shortcut.h"
#include "render_core/input_event.h"
{{FILE:sfw/render_core/shortcut.cpp}}
#include "render_core/material.h"
{{FILE:sfw/render_core/material.cpp}}
//{//{FILE:sfw/render_core/primitive_meshes.cpp}}
#include "render_core/image.h"
#include "core/error_macros.h"
#include "core/hash_map.h"
#include "math.h"
#include "core/memory.h"
#include "core/vector3.h"
#include "3rd_stb_image.h"
{{FILE:sfw/render_core/image.cpp}}
#include "render_core/window.h"
#include "render_core/3rd_glad.h"
#include "3rd_glfw3.h"
#include "core/error_macros.h"
#include "core/stime.h"
#include "core/ustring.h"
#include "core/vector4.h"
#include "render_core/application.h"
#include "render_core/input.h"
{{FILE:sfw/render_core/window.cpp}}
#include "keyboard.h"
{{FILE:sfw/render_core/keyboard.cpp}}
#include "input_map.h"
#include "render_core/input.h"
#include "render_core/keyboard.h"
{{FILE:sfw/render_core/input_map.cpp}}
#include "render_core/scene.h"
#include "render_core/input_event.h"
{{FILE:sfw/render_core/scene.cpp}}
#include "input.h"
#include "core/logger.h"
#include "core/stime.h"
#include "render_core/application.h"
#include "render_core/input_map.h"
#include "render_core/keyboard.h"
#include "render_core/texture.h"
#include "render_core/window.h"
#include "render_core/3rd_glfw3.h"
{{FILE:sfw/render_core/input.cpp}}

#include "renderer.h"
#include "render_core/color_material_2d.h"
#include "render_core/font.h"
#include "render_core/font_material.h"
#include "render_core/material.h"
#include "render_core/mesh.h"
#include "render_core/texture.h"
#include "render_core/texture_material_2d.h"
#include "render_core/window.h"
#include "render_core/render_state.h"
{{FILE:sfw/render_immediate/renderer.cpp}}

#include "render_objects/camera_3d.h"
#include "core/math_funcs.h"
#include "render_core/render_state.h"
{{FILE:sfw/render_objects/camera_3d.cpp}}
#include "render_objects/sprite.h"
{{FILE:sfw/render_objects/sprite.cpp}}
#include "render_objects/camera_2d.h"
#include "core/math_funcs.h"
#include "render_core/render_state.h"
{{FILE:sfw/render_objects/camera_2d.cpp}}
#include "render_objects/mesh_instance_3d.h"
#include "render_objects/camera_3d.h"
{{FILE:sfw/render_objects/mesh_instance_3d.cpp}}
#include "render_objects/object_3d.h"
{{FILE:sfw/render_objects/object_3d.cpp}}
#include "render_objects/tile_map.h"
#include "render_objects/camera_2d.h"
{{FILE:sfw/render_objects/tile_map.cpp}}
#include "render_objects/text_2d.h"
#include "render_core/font.h"
#include "render_core/font_material.h"
#include "render_core/mesh.h"
#include "render_objects/camera_2d.h"
{{FILE:sfw/render_objects/text_2d.cpp}}
#include "render_objects/object_2d.h"
{{FILE:sfw/render_objects/object_2d.cpp}}
#include "render_objects/mesh_instance_2d.h"
#include "render_objects/camera_2d.h"
{{FILE:sfw/render_objects/mesh_instance_2d.cpp}}



