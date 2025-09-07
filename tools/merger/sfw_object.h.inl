#ifndef SFW_H
#define SFW_H

{{FILEINLINE:sfw/core/version.h}}

{{FILEINLINE:tools/merger/sfw_readme.inl.h}}

// MODULES:
// CORE + OBJECT

// LICENSES:

{{FILEINLINE:tools/merger/sfw_linceses_core.inl.h}}

#ifndef _REENTRANT
#define _REENTRANT
#endif

#include <float.h>
#include <math.h>
#include <string.h>
#include <stddef.h>

//===================  CORE SECTION  ===================

//--STRIP
//no includes
//--STRIP
{{FILE:sfw/core/int_types.h}}
//--STRIP
//no includes
//--STRIP
{{FILE:sfw/core/math_defs.h}}
//--STRIP
//no includes
//--STRIP
{{FILE:sfw/core/error_list.h}}
//--STRIP
//no includes
//--STRIP
{{FILE:sfw/core/logger.h}}

//--STRIP
//#include "core/int_types.h"
//#include "core/error_list.h"
//--STRIP
{{FILE:sfw/core/typedefs.h}}

//--STRIP
//#include "core/int_types.h"
//#include "core/math_defs.h"
//--STRIP
{{FILE:sfw/core/marshalls.h}}

//--STRIP
//#include "core/int_types.h"
//--STRIP
{{FILE:sfw/core/sfw_time.h}}
//--STRIP
//#include "core/typedefs.h"
//--STRIP
{{FILE:sfw/core/safe_refcount.h}}
//--STRIP
//#include "core/typedefs.h"
//#if !defined(NO_THREADS)
//#include "core/safe_refcount.h"
//#include <thread>
//#endif
//--STRIP
{{FILE:sfw/core/thread.h}}

//--STRIP
//#include "core/logger.h"
//#include "core/typedefs.h"
//--STRIP
{{FILE:sfw/core/error_macros.h}}


//--STRIP
//#include "core/error_macros.h"
//#include "core/safe_refcount.h"
//--STRIP
{{FILE:sfw/core/memory.h}}


//--STRIP
//#include "core/error_list.h"
//#include "core/typedefs.h"
//--STRIP
{{FILE:sfw/core/mutex.h}}
//--STRIP
//#include "core/error_list.h"
//--STRIP
{{FILE:sfw/core/rw_lock.h}}
//--STRIP
//#include "core/typedefs.h"
//--STRIP
{{FILE:sfw/core/spin_lock.h}}
//--STRIP
//#include "core/mutex.h"
//--STRIP
{{FILE:sfw/core/thread_safe.h}}

{{FILE:sfw/core/semaphore.h}}

//--STRIP
//#include "core/typedefs.h"
//--STRIP
{{FILE:sfw/core/pcg.h}}
//--STRIP
//#include "core/math_defs.h"
//#include "core/pcg.h"
//--STRIP
{{FILE:sfw/core/random_pcg.h}}

//--STRIP
//#include "core/error_macros.h"
//#include "core/math_defs.h"
//#include "core/random_pcg.h"
//#include "core/typedefs.h"
//#include "core/pcg.h"
//--STRIP
{{FILE:sfw/core/math_funcs.h}}

//--STRIP
//Simple almost dependencyless containers
//--STRIP

//--STRIP
//#include "core/error_list.h"
//#include "core/error_macros.h"
//#include "core/memory.h"
//#include "core/safe_refcount.h"
//--STRIP
{{FILE:sfw/core/cowdata.h}}
//--STRIP
//#include "core/error_macros.h"
//#include "core/typedefs.h"
//--STRIP
{{FILE:sfw/core/sort_array.h}}
//--STRIP
//#include "core/error_macros.h"
//#include "core/memory.h"
//--STRIP
{{FILE:sfw/core/rb_map.h}}
//--STRIP
//#include "core/memory.h"
//#include "core/typedefs.h"
//--STRIP
{{FILE:sfw/core/rb_set.h}}
//--STRIP
//#include "cowdata.h"
//#include "core/typedefs.h"
//--STRIP
{{FILE:sfw/core/vmap.h}}
//--STRIP
//#include "cowdata.h"
//#include "core/sort_array.h"
//#include "core/error_macros.h"
//#include "core/memory.h"
//--STRIP
{{FILE:sfw/core/vector.h}}
//--STRIP
//#include "core/vector.h"
//#include "core/typedefs.h"
//--STRIP
{{FILE:sfw/core/vset.h}}
//--STRIP
//#include "core/sort_array.h"
//#include "core/error_macros.h"
//#include "core/memory.h"
//--STRIP
{{FILE:sfw/core/list.h}}
//--STRIP
//#include "core/vector.h"
//--STRIP
{{FILE:sfw/core/ring_buffer.h}}
//--STRIP
//#include "core/memory.h"
//#include "spin_lock.h"
//#include "core/typedefs.h"
//--STRIP
{{FILE:sfw/core/paged_allocator.h}}
//--STRIP
//#include "core/typedefs.h"
//--STRIP
{{FILE:sfw/core/pool_allocator.h}}

//--STRIP
//Strings they need vector.h, and cowdata.h
//--STRIP

//--STRIP
//#include "core/typedefs.h"
//--STRIP
{{FILE:sfw/core/char_range.inc}}
//--STRIP
//#include "core/typedefs.h"
//#include "core/char_range.inc"
//--STRIP
{{FILE:sfw/core/char_utils.h}}
//--STRIP
//#include "cowdata.h"
//#include "core/vector.h"
//#include "char_utils.h"
//#include "core/typedefs.h"
//--STRIP
{{FILE:sfw/core/ustring.h}}

//--STRIP
//#include "core/mutex.h"
//#include "core/safe_refcount.h"
//#include "core/ustring.h"
//--STRIP
{{FILE:sfw/core/string_name.h}}

//--STRIP
//Needs ustring.h
//--STRIP

//--STRIP
//#include "core/memory.h"
//#include "core/mutex.h"
//#include "pool_allocator.h"
//#include "rw_lock.h"
//#include "core/safe_refcount.h"
//#include "core/ustring.h"
//--STRIP
{{FILE:sfw/core/pool_vector.h}}
//--STRIP
//#include "core/pool_vector.h"
//#include "core/sort_array.h"
//#include "core/vector.h"
//#include "core/error_macros.h"
//#include "core/memory.h"
//--STRIP
{{FILE:sfw/core/tight_local_vector.h}}
//--STRIP
//#include "core/pool_vector.h"
//#include "core/sort_array.h"
//#include "core/vector.h"
//#include "core/error_macros.h"
//#include "core/memory.h"
//--STRIP
{{FILE:sfw/core/local_vector.h}}

//--STRIP
//Math classes
//--STRIP

//--STRIP
//#include "core/math_funcs.h"
//#include "core/ustring.h"
//--STRIP
{{FILE:sfw/core/color.h}}
//--STRIP
//#include "core/math_funcs.h"
//#include "core/error_macros.h"
//--STRIP
{{FILE:sfw/core/vector2.h}}
//--STRIP
//#include "core/error_macros.h"
//#include "core/math_funcs.h"
//#include "core/vector2.h"
//--STRIP
{{FILE:sfw/core/vector2i.h}}
//--STRIP
//#include "core/vector2.h" // also includes math_funcs and ustring
//#include "core/vector2i.h"
//--STRIP
{{FILE:sfw/core/rect2.h}}
//--STRIP
//#include "core/vector2i.h" // also includes math_funcs and ustring
//#include "core/rect2.h"
//--STRIP
{{FILE:sfw/core/rect2i.h}}
//--STRIP
//#include "core/math_funcs.h"
//#include "core/ustring.h"
//--STRIP
{{FILE:sfw/core/vector3.h}}
//--STRIP
//#include "core/error_macros.h"
//#include "core/math_funcs.h"
//--STRIP
{{FILE:sfw/core/vector3i.h}}
//--STRIP
//#include "core/math_defs.h"
//#include "core/math_funcs.h"
//#include "core/ustring.h"
//--STRIP
{{FILE:sfw/core/vector4.h}}
//--STRIP
//#include "core/error_macros.h"
//#include "core/math_funcs.h"
//--STRIP
{{FILE:sfw/core/vector4i.h}}

//--STRIP
//#include "core/vector3.h"
//--STRIP
{{FILE:sfw/core/plane.h}}
//--STRIP
//#include "core/math_defs.h"
//#include "core/plane.h"
//#include "core/vector3.h"
//--STRIP
{{FILE:sfw/core/aabb.h}}
//--STRIP
//#include "core/math_defs.h"
//#include "core/math_funcs.h"
//#include "core/vector3.h"
//#include "core/ustring.h"
//--STRIP
{{FILE:sfw/core/quaternion.h}}
//--STRIP
//#include "core/vector.h"
//#include "core/math_defs.h"
//#include "core/vector3.h"
//#include "core/math_defs.h"
//#include "core/math_funcs.h"
//#include "core/ustring.h"
//#include "core/vector4.h"
//--STRIP
{{FILE:sfw/core/projection.h}}
//--STRIP
//#include "core/quaternion.h"
//#include "core/vector3.h"
//#include "core/vector3i.h"
//--STRIP
{{FILE:sfw/core/basis.h}}

//--STRIP
//#include "core/pool_vector.h"
//#include "core/rect2.h" // also includes vector2, math_funcs, and ustring
//#include "core/rect2i.h" // also includes vector2i, math_funcs, and ustring
//--STRIP
{{FILE:sfw/core/transform_2d.h}}
//--STRIP
//#include "core/aabb.h"
//#include "core/plane.h"
//#include "core/transform.h"
//#include "core/vector3.h"
//--STRIP
{{FILE:sfw/core/face3.h}}
//--STRIP
//#include "core/aabb.h"
//#include "core/basis.h"
//#include "core/plane.h"
//#include "core/vector3i.h"
//#include "core/pool_vector.h"
//--STRIP
{{FILE:sfw/core/transform.h}}

//--STRIP
//hashfuncs.h Needs most math classes
//--STRIP

//--STRIP
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
//--STRIP
{{FILE:sfw/core/hashfuncs.h}}

//--STRIP
//Containers that need hashfuncs.h
//--STRIP

//--STRIP
//#include "core/hashfuncs.h"
//#include "core/typedefs.h"
//--STRIP
{{FILE:sfw/core/pair.h}}
//--STRIP
//#include "core/hashfuncs.h"
//#include "core/list.h"
//#include "core/error_macros.h"
//#include "core/math_funcs.h"
//#include "core/memory.h"
//#include "core/ustring.h"
//--STRIP
{{FILE:sfw/core/og_hash_map.h}}
//--STRIP
//#include "core/list.h"
//#include "core/og_hash_map.h"
//#include "core/pair.h"
//--STRIP
{{FILE:sfw/core/ordered_hash_map.h}}
//--STRIP
//#include "core/hashfuncs.h"
//#include "paged_allocator.h"
//#include "pair.h"
//#include "core/math_funcs.h"
//#include "core/memory.h"
//#include "list.h"
//--STRIP
{{FILE:sfw/core/hash_map.h}}
//--STRIP
//#include "core/hash_map.h"
//#include "core/hashfuncs.h"
//#include "core/math_funcs.h"
//#include "core/memory.h"
//--STRIP
{{FILE:sfw/core/hash_set.h}}

//--STRIP
//#include "core/ustring.h"
//--STRIP
{{FILE:sfw/core/string_buffer.h}}

//--STRIP
//#include "core/ustring.h"
//#include "core/vector.h"
//--STRIP
{{FILE:sfw/core/string_builder.h}}

//--STRIP
//#include "core/error_list.h"
//#include "core/ustring.h"
//also needs vector
//--STRIP
{{FILE:sfw/core/file_access.h}}

//--STRIP
//#include "core/error_list.h"
//#include "core/ustring.h"
//--STRIP
{{FILE:sfw/core/dir_access.h}}


//--STRIP
//#include "int_types.h"
//#include "core/ustring.h"
//--STRIP
{{FILE:sfw/core/inet_address.h}}
//--STRIP
//#include "inet_address.h"
//--STRIP
{{FILE:sfw/core/socket.h}}

//--STRIP
//#include "core/list.h"
//#include "core/math_defs.h"
//#include "core/memory.h"
//#include "core/mutex.h"
//#include "core/typedefs.h"
//#include "core/ustring.h"
//#include <stdio.h>
//Win Only
//#include "core/local_vector.h"
//--STRIP
{{FILE:sfw/core/sub_process.h}}

//--STRIP
//no includes
//--STRIP
{{FILE:sfw/core/sfw_core.h}}

//===================  OBJECT SECTION  ===================

//--STRIP
//Dependencyless stuff
//--STRIP

//--STRIP
//#include "core/typedefs.h"
//--STRIP
{{FILE:sfw/object/ref_ptr.h}}
//--STRIP
//#include "core/int_types.h"
//--STRIP
{{FILE:sfw/object/object_id.h}}

//--STRIP
//#include "core/string_name.h"
//--STRIP
{{FILE:sfw/object/core_string_names.h}}

//--STRIP
//Variants
//--STRIP

//--STRIP
//#include "core/typedefs.h"
//--STRIP
{{FILE:sfw/object/array.h}}

//--STRIP
//#include "core/list.h"
//#include "core/ustring.h"
//#include "object/array.h"
//--STRIP
{{FILE:sfw/object/dictionary.h}}

//--STRIP
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
//--STRIP
{{FILE:sfw/object/variant.h}}

//--STRIP
//Stuff that needs Variant
//--STRIP

//--STRIP
//#include "core/vector.h"
//#include "core/ustring.h"
//#include "object/variant.h"
//#include "object/reference.h"
//--STRIP
{{FILE:sfw/object/psignal.h}}

//--STRIP
//#include "core/hash_map.h"
//#include "core/rw_lock.h"
//#include "core/string_name.h"
//#include "core/ustring.h"
//#include "core/vector.h"
//#include "object/object_id.h"
//#include "object/variant.h"
//#include "object/dictionary.h"
//--STRIP
{{FILE:sfw/object/object.h}}


//--STRIP
//#include "core/memory.h"
//#include "core/typedefs.h"
//--STRIP
{{FILE:sfw/object/object_rc.h}}

//--STRIP
//#include "core/memory.h"
//#include "core/safe_refcount.h"
//#include "object/object.h"
//#include "object/ref_ptr.h"
//--STRIP
{{FILE:sfw/object/reference.h}}

//--STRIP
//#include "object/reference.h"
//#include "psignal.h"
//--STRIP
{{FILE:sfw/object/resource.h}}

#endif
