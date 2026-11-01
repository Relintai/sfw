

# You might need to add -std=c++14 depending on your compiler version

ccache g++ -Wall -D_REENTRANT -g -I. -c core/color.cpp -o core/color.o
ccache g++ -Wall -D_REENTRANT -g -I. -c core/logger.cpp -o core/logger.o
ccache g++ -Wall -D_REENTRANT -g -I. -c core/math_funcs.cpp -o core/math_funcs.o
ccache g++ -Wall -D_REENTRANT -g -I. -c core/memory.cpp -o core/memory.o
ccache g++ -Wall -D_REENTRANT -g -I. -c core/pcg.cpp -o core/pcg.o
ccache g++ -Wall -D_REENTRANT -g -I. -c core/random_pcg.cpp -o core/random_pcg.o
ccache g++ -Wall -D_REENTRANT -g -I. -c core/safe_refcount.cpp -o core/safe_refcount.o
ccache g++ -Wall -D_REENTRANT -g -I. -c core/ustring.cpp -o core/ustring.o
ccache g++ -Wall -D_REENTRANT -g -I. -c core/string_name.cpp -o core/string_name.o

ccache g++ -Wall -D_REENTRANT -g -I. -c core/rect2i.cpp -o core/rect2i.o
ccache g++ -Wall -D_REENTRANT -g -I. -c core/vector2i.cpp -o core/vector2i.o

ccache g++ -Wall -D_REENTRANT -g -I. -c core/file_access.cpp -o core/file_access.o
ccache g++ -Wall -D_REENTRANT -g -I. -c core/dir_access.cpp -o core/dir_access.o

ccache g++ -Wall -D_REENTRANT -g -I. -c core/pool_vector.cpp -o core/pool_vector.o
ccache g++ -Wall -D_REENTRANT -g -I. -c core/pool_allocator.cpp -o core/pool_allocator.o
ccache g++ -Wall -D_REENTRANT -g -I. -c core/mutex.cpp -o core/mutex.o
ccache g++ -Wall -D_REENTRANT -g -I. -c core/rw_lock.cpp -o core/rw_lock.o
ccache g++ -Wall -D_REENTRANT -g -I. -c core/semaphore.cpp -o core/semaphore.o
ccache g++ -Wall -D_REENTRANT -g -I. -c core/sfw_time.cpp -o core/sfw_time.o
ccache g++ -Wall -D_REENTRANT -g -I. -c core/string_builder.cpp -o core/string_builder.o

ccache g++ -Wall -D_REENTRANT -g -I. -c core/thread.cpp -o core/thread.o
ccache g++ -Wall -D_REENTRANT -g -I. -c core/socket.cpp -o core/socket.o
ccache g++ -Wall -D_REENTRANT -g -I. -c core/inet_address.cpp -o core/inet_address.o

ccache g++ -Wall -D_REENTRANT -g -I. -c core/sub_process.cpp -o core/sub_process.o

ccache g++ -Wall -D_REENTRANT -g -I. -c core/sfw_core.cpp -o core/sfw_core.o

ccache g++ -Wall -D_REENTRANT -g -I. -c core/os.cpp -o core/os.o

ccache g++ -Wall -D_REENTRANT -g -I. -c object/object.cpp -o object/object.o
ccache g++ -Wall -D_REENTRANT -g -I. -c object/reference.cpp -o object/reference.o
ccache g++ -Wall -D_REENTRANT -g -I. -c object/core_string_names.cpp -o object/core_string_names.o
ccache g++ -Wall -D_REENTRANT -g -I. -c object/variant.cpp -o object/variant.o
ccache g++ -Wall -D_REENTRANT -g -I. -c object/variant_op.cpp -o object/variant_op.o
ccache g++ -Wall -D_REENTRANT -g -I. -c object/psignal.cpp -o object/psignal.o
ccache g++ -Wall -D_REENTRANT -g -I. -c object/array.cpp -o object/array.o
ccache g++ -Wall -D_REENTRANT -g -I. -c object/dictionary.cpp -o object/dictionary.o
ccache g++ -Wall -D_REENTRANT -g -I. -c object/ref_ptr.cpp -o object/ref_ptr.o
ccache g++ -Wall -D_REENTRANT -g -I. -c object/resource.cpp -o object/resource.o

ccache g++ -Wall -D_REENTRANT -g -I. -c main.cpp -o main.o

# You might need to add -lpthread and/or -latomic depending on your compiler version  (add it near -lX11)

ccache g++ -Wall -D_REENTRANT -g  core/color.o core/rect2i.o core/vector2i.o \
                        core/logger.o core/math_funcs.o \
                        core/memory.o core/pcg.o core/random_pcg.o \
                        core/safe_refcount.o \
                        core/ustring.o core/string_name.o \
                        core/pool_vector.o core/pool_allocator.o core/mutex.o core/sfw_time.o \
												core/rw_lock.o core/semaphore.o \
												core/string_builder.o \
                        core/dir_access.o core/file_access.o core/thread.o \
                        core/socket.o core/inet_address.o \
                        core/sub_process.o \
                        core/sfw_core.o \
                        core/os.o \
                        object/object.o object/reference.o object/core_string_names.o \
                        object/variant.o object/variant_op.o object/psignal.o \
                        object/array.o object/dictionary.o object/ref_ptr.o \
                        object/resource.o \
                        main.o \
                        -o sfwl_app 

