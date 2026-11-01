@echo off

if not defined DevEnvDir (
	call "C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvarsall.bat" amd64
)

rem debug: /Zi (== -g)

rem you might need to add /std:c++14 depending on your compiler version.

cl /D_REENTRANT /EHsc /Zi /I. /c core/color.cpp /Fo:core/color.obj
cl /D_REENTRANT /EHsc /Zi /I. /c core/logger.cpp /Fo:core/logger.obj
cl /D_REENTRANT /EHsc /Zi /I. /c core/math_funcs.cpp /Fo:core/math_funcs.obj
cl /D_REENTRANT /EHsc /Zi /I. /c core/memory.cpp /Fo:core/memory.obj
cl /D_REENTRANT /EHsc /Zi /I. /c core/pcg.cpp /Fo:core/pcg.obj
cl /D_REENTRANT /EHsc /Zi /I. /c core/random_pcg.cpp /Fo:core/random_pcg.obj
cl /D_REENTRANT /EHsc /Zi /I. /c core/rect2i.cpp /Fo:core/rect2i.obj
cl /D_REENTRANT /EHsc /Zi /I. /c core/safe_refcount.cpp /Fo:core/safe_refcount.obj
cl /D_REENTRANT /EHsc /Zi /I. /c core/ustring.cpp /Fo:core/ustring.obj
cl /D_REENTRANT /EHsc /Zi /I. /c core/string_name.cpp /Fo:core/string_name.obj
cl /D_REENTRANT /EHsc /Zi /I. /c core/vector2i.cpp /Fo:core/vector2i.obj

cl /D_REENTRANT /EHsc /Zi /I. /c core/file_access.cpp /Fo:core/file_access.obj
cl /D_REENTRANT /EHsc /Zi /I. /c core/dir_access.cpp /Fo:core/dir_access.obj

cl /D_REENTRANT /EHsc /Zi /I. /c core/pool_vector.cpp /Fo:core/pool_vector.obj
cl /D_REENTRANT /EHsc /Zi /I. /c core/pool_allocator.cpp /Fo:core/pool_allocator.obj
cl /D_REENTRANT /EHsc /Zi /I. /c core/mutex.cpp /Fo:core/mutex.obj
cl /D_REENTRANT /EHsc /Zi /I. /c core/rw_lock.cpp /Fo:core/rw_lock.obj
cl /D_REENTRANT /EHsc /Zi /I. /c core/semaphore.cpp /Fo:core/semaphore.obj
cl /D_REENTRANT /EHsc /Zi /I. /c core/sfw_time.cpp /Fo:core/sfw_time.obj
cl /D_REENTRANT /EHsc /Zi /I. /c core/string_builder.cpp /Fo:core/string_builder.obj

cl /D_REENTRANT /EHsc /Zi /I. /c core/thread.cpp /Fo:core/thread.obj
cl /D_REENTRANT /EHsc /Zi /I. /c core/socket.cpp /Fo:core/socket.obj
cl /D_REENTRANT /EHsc /Zi /I. /c core/inet_address.cpp /Fo:core/inet_address.obj

cl /D_REENTRANT /EHsc /Zi /I. /c core/sub_process.cpp /Fo:core/sub_process.obj

cl /D_REENTRANT /EHsc /Zi /I. /c core/sfw_core.cpp /Fo:core/sfw_core.obj

cl /D_REENTRANT /EHsc /Zi /I. /c core/os.cpp /Fo:core/os.obj

cl /D_REENTRANT /EHsc /Zi /I. /c object/object.cpp /Fo:object/object.obj
cl /D_REENTRANT /EHsc /Zi /I. /c object/reference.cpp /Fo:object/reference.obj
cl /D_REENTRANT /EHsc /Zi /I. /c object/core_string_names.cpp /Fo:object/core_string_names.obj
cl /D_REENTRANT /EHsc /Zi /I. /c object/variant.cpp /Fo:object/variant.obj
cl /D_REENTRANT /EHsc /Zi /I. /c object/variant_op.cpp /Fo:object/variant_op.obj
cl /D_REENTRANT /EHsc /Zi /I. /c object/psignal.cpp /Fo:object/psignal.obj
cl /D_REENTRANT /EHsc /Zi /I. /c object/array.cpp /Fo:object/array.obj
cl /D_REENTRANT /EHsc /Zi /I. /c object/dictionary.cpp /Fo:object/dictionary.obj
cl /D_REENTRANT /EHsc /Zi /I. /c object/ref_ptr.cpp /Fo:object/ref_ptr.obj
cl /D_REENTRANT /EHsc /Zi /I. /c object/resource.cpp /Fo:object/resource.obj

cl /D_REENTRANT /EHsc /Zi /I. /c main.cpp /Fo:main.obj


cl /D_REENTRANT /Zi ^
		/EHsc ^
		/Fegame-vc.exe ^
		core/color.obj ^
		core/logger.obj core/math_funcs.obj ^
		core/memory.obj core/pcg.obj core/random_pcg.obj ^
		core/rect2i.obj core/safe_refcount.obj ^
		core/ustring.obj core/string_name.obj ^
		core/vector2i.obj ^
		core/pool_vector.obj core/pool_allocator.obj core/mutex.obj core/sfw_time.obj ^
		core/rw_lock.obj core/semaphore.obj ^
		core/string_builder.obj ^
		core/dir_access.obj core/file_access.obj core/thread.obj ^
		core/socket.obj core/inet_address.obj ^
		core/sub_process.obj ^
		core/sfw_core.obj ^
		core/os.obj ^
		object/object.obj object/reference.obj object/core_string_names.obj ^
		object/variant.obj object/variant_op.obj object/psignal.obj ^
		object/array.obj object/dictionary.obj object/ref_ptr.obj ^
		object/resource.obj ^
		main.obj ^
		/SUBSYSTEM:CONSOLE
