@echo off

if not defined DevEnvDir (
	call "C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvarsall.bat" amd64
)

rem debug: /Zi (== -g)

rem you might need to add /std:c++14 depending on your compiler version.

cl /D_REENTRANT /EHsc /Zi /Isfwl /c sfwl/core/color.cpp /Fo:sfwl/core/color.obj
cl /D_REENTRANT /EHsc /Zi /Isfwl /c sfwl/core/logger.cpp /Fo:sfwl/core/logger.obj
cl /D_REENTRANT /EHsc /Zi /Isfwl /c sfwl/core/math_funcs.cpp /Fo:sfwl/core/math_funcs.obj
cl /D_REENTRANT /EHsc /Zi /Isfwl /c sfwl/core/memory.cpp /Fo:sfwl/core/memory.obj
cl /D_REENTRANT /EHsc /Zi /Isfwl /c sfwl/core/pcg.cpp /Fo:sfwl/core/pcg.obj
cl /D_REENTRANT /EHsc /Zi /Isfwl /c sfwl/core/random_pcg.cpp /Fo:sfwl/core/random_pcg.obj
cl /D_REENTRANT /EHsc /Zi /Isfwl /c sfwl/core/rect2i.cpp /Fo:sfwl/core/rect2i.obj
cl /D_REENTRANT /EHsc /Zi /Isfwl /c sfwl/core/safe_refcount.cpp /Fo:sfwl/core/safe_refcount.obj
cl /D_REENTRANT /EHsc /Zi /Isfwl /c sfwl/core/ustring.cpp /Fo:sfwl/core/ustring.obj
cl /D_REENTRANT /EHsc /Zi /Isfwl /c sfwl/core/string_name.cpp /Fo:sfwl/core/string_name.obj
cl /D_REENTRANT /EHsc /Zi /Isfwl /c sfwl/core/vector2i.cpp /Fo:sfwl/core/vector2i.obj

cl /D_REENTRANT /EHsc /Zi /Isfwl /c sfwl/core/file_access.cpp /Fo:sfwl/core/file_access.obj
cl /D_REENTRANT /EHsc /Zi /Isfwl /c sfwl/core/dir_access.cpp /Fo:sfwl/core/dir_access.obj

cl /D_REENTRANT /EHsc /Zi /Isfwl /c sfwl/core/pool_vector.cpp /Fo:sfwl/core/pool_vector.obj
cl /D_REENTRANT /EHsc /Zi /Isfwl /c sfwl/core/pool_allocator.cpp /Fo:sfwl/core/pool_allocator.obj
cl /D_REENTRANT /EHsc /Zi /Isfwl /c sfwl/core/mutex.cpp /Fo:sfwl/core/mutex.obj
cl /D_REENTRANT /EHsc /Zi /Isfwl /c sfwl/core/rw_lock.cpp /Fo:sfwl/core/rw_lock.obj
cl /D_REENTRANT /EHsc /Zi /Isfwl /c sfwl/core/semaphore.cpp /Fo:sfwl/core/semaphore.obj
cl /D_REENTRANT /EHsc /Zi /Isfwl /c sfwl/core/sfw_time.cpp /Fo:sfwl/core/sfw_time.obj
cl /D_REENTRANT /EHsc /Zi /Isfwl /c sfwl/core/string_builder.cpp /Fo:sfwl/core/string_builder.obj

cl /D_REENTRANT /EHsc /Zi /Isfwl /c sfwl/core/thread.cpp /Fo:sfwl/core/thread.obj
cl /D_REENTRANT /EHsc /Zi /Isfwl /c sfwl/core/socket.cpp /Fo:sfwl/core/socket.obj
cl /D_REENTRANT /EHsc /Zi /Isfwl /c sfwl/core/inet_address.cpp /Fo:sfwl/core/inet_address.obj

cl /D_REENTRANT /EHsc /Zi /Isfwl /c sfwl/core/sub_process.cpp /Fo:sfwl/core/sub_process.obj

cl /D_REENTRANT /EHsc /Zi /Isfwl /c sfwl/core/sfw_core.cpp /Fo:sfwl/core/sfw_core.obj

cl /D_REENTRANT /EHsc /Zi /Isfwl /c sfwl/core/os.cpp /Fo:sfwl/core/os.obj

cl /D_REENTRANT /EHsc /Zi /Isfwl /c sfwl/object/object.cpp /Fo:sfwl/object/object.obj
cl /D_REENTRANT /EHsc /Zi /Isfwl /c sfwl/object/reference.cpp /Fo:sfwl/object/reference.obj
cl /D_REENTRANT /EHsc /Zi /Isfwl /c sfwl/object/core_string_names.cpp /Fo:sfwl/object/core_string_names.obj
cl /D_REENTRANT /EHsc /Zi /Isfwl /c sfwl/object/variant.cpp /Fo:sfwl/object/variant.obj
cl /D_REENTRANT /EHsc /Zi /Isfwl /c sfwl/object/variant_op.cpp /Fo:sfwl/object/variant_op.obj
cl /D_REENTRANT /EHsc /Zi /Isfwl /c sfwl/object/psignal.cpp /Fo:sfwl/object/psignal.obj
cl /D_REENTRANT /EHsc /Zi /Isfwl /c sfwl/object/array.cpp /Fo:sfwl/object/array.obj
cl /D_REENTRANT /EHsc /Zi /Isfwl /c sfwl/object/dictionary.cpp /Fo:sfwl/object/dictionary.obj
cl /D_REENTRANT /EHsc /Zi /Isfwl /c sfwl/object/ref_ptr.cpp /Fo:sfwl/object/ref_ptr.obj
cl /D_REENTRANT /EHsc /Zi /Isfwl /c sfwl/object/resource.cpp /Fo:sfwl/object/resource.obj

cl /D_REENTRANT /EHsc /Zi /Isfwl /c sfwl/main.cpp /Fo:sfwl/main.obj


cl /D_REENTRANT /Zi ^
		/EHsc ^
		/Fegame-vc.exe ^
		sfwl/core/color.obj ^
		sfwl/core/logger.obj sfwl/core/math_funcs.obj ^
		sfwl/core/memory.obj sfwl/core/pcg.obj sfwl/core/random_pcg.obj ^
		sfwl/core/rect2i.obj sfwl/core/safe_refcount.obj ^
		sfwl/core/ustring.obj sfwl/core/string_name.obj ^
		sfwl/core/vector2i.obj ^
		sfwl/core/pool_vector.obj sfwl/core/pool_allocator.obj sfwl/core/mutex.obj sfwl/core/sfw_time.obj ^
		sfwl/core/rw_lock.obj sfwl/core/semaphore.obj ^
		sfwl/core/string_builder.obj ^
		sfwl/core/dir_access.obj sfwl/core/file_access.obj sfwl/core/thread.obj ^
		sfwl/core/socket.obj sfwl/core/inet_address.obj ^
		sfwl/core/sub_process.obj ^
		sfwl/core/sfw_core.obj ^
		sfwl/core/os.obj ^
		sfwl/object/object.obj sfwl/object/reference.obj sfwl/object/core_string_names.obj ^
		sfwl/object/variant.obj sfwl/object/variant_op.obj sfwl/object/psignal.obj ^
		sfwl/object/array.obj sfwl/object/dictionary.obj sfwl/object/ref_ptr.obj ^
		sfwl/object/resource.obj ^
		sfwl/main.obj ^
		/SUBSYSTEM:CONSOLE
