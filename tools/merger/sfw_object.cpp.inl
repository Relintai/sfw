

{{FILEINLINE:tools/merger/sfw_readme.inl.h}}

// MODULES:
// CORE + OBJECT

// LICENSES:

{{FILEINLINE:tools/merger/sfw_linceses_core.inl.h}}

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
#include "sfw.h"
#endif

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
//#include "thread.h"
//#include "core/error_macros.h"
//#include "core/safe_refcount.h"
//--STRIP
{{FILE:sfw/core/thread.cpp}}

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
//#include "core/sfw_time.h"
//--STRIP
{{FILE:sfw/core/sfw_time.cpp}}

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
//Windows:
//#include <windows.h>
//#include <winnt.h>
//Linux
//#include <unistd.h>
//--STRIP
{{FILE:sfw/core/os.cpp}}

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
