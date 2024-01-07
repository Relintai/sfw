

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

#ifndef SFWL_H
#include "sfwl.h"
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
