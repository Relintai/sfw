

# You might need to add -std=c++14 depending on your compiler version

ccache g++ -Wall -D_REENTRANT -g -Isfwl -c sfwl/core/color.cpp -o sfwl/core/color.o
ccache g++ -Wall -D_REENTRANT -g -Isfwl -c sfwl/core/logger.cpp -o sfwl/core/logger.o
ccache g++ -Wall -D_REENTRANT -g -Isfwl -c sfwl/core/math_funcs.cpp -o sfwl/core/math_funcs.o
ccache g++ -Wall -D_REENTRANT -g -Isfwl -c sfwl/core/memory.cpp -o sfwl/core/memory.o
ccache g++ -Wall -D_REENTRANT -g -Isfwl -c sfwl/core/pcg.cpp -o sfwl/core/pcg.o
ccache g++ -Wall -D_REENTRANT -g -Isfwl -c sfwl/core/random_pcg.cpp -o sfwl/core/random_pcg.o
ccache g++ -Wall -D_REENTRANT -g -Isfwl -c sfwl/core/safe_refcount.cpp -o sfwl/core/safe_refcount.o
ccache g++ -Wall -D_REENTRANT -g -Isfwl -c sfwl/core/ustring.cpp -o sfwl/core/ustring.o
ccache g++ -Wall -D_REENTRANT -g -Isfwl -c sfwl/core/string_name.cpp -o sfwl/core/string_name.o

ccache g++ -Wall -D_REENTRANT -g -Isfwl -c sfwl/core/rect2i.cpp -o sfwl/core/rect2i.o
ccache g++ -Wall -D_REENTRANT -g -Isfwl -c sfwl/core/vector2i.cpp -o sfwl/core/vector2i.o

ccache g++ -Wall -D_REENTRANT -g -Isfwl -c sfwl/core/file_access.cpp -o sfwl/core/file_access.o
ccache g++ -Wall -D_REENTRANT -g -Isfwl -c sfwl/core/dir_access.cpp -o sfwl/core/dir_access.o

ccache g++ -Wall -D_REENTRANT -g -Isfwl -c sfwl/core/pool_vector.cpp -o sfwl/core/pool_vector.o
ccache g++ -Wall -D_REENTRANT -g -Isfwl -c sfwl/core/pool_allocator.cpp -o sfwl/core/pool_allocator.o
ccache g++ -Wall -D_REENTRANT -g -Isfwl -c sfwl/core/mutex.cpp -o sfwl/core/mutex.o
ccache g++ -Wall -D_REENTRANT -g -Isfwl -c sfwl/core/rw_lock.cpp -o sfwl/core/rw_lock.o
ccache g++ -Wall -D_REENTRANT -g -Isfwl -c sfwl/core/semaphore.cpp -o sfwl/core/semaphore.o
ccache g++ -Wall -D_REENTRANT -g -Isfwl -c sfwl/core/sfw_time.cpp -o sfwl/core/sfw_time.o
ccache g++ -Wall -D_REENTRANT -g -Isfwl -c sfwl/core/string_builder.cpp -o sfwl/core/string_builder.o

ccache g++ -Wall -D_REENTRANT -g -Isfwl -c sfwl/core/thread.cpp -o sfwl/core/thread.o
ccache g++ -Wall -D_REENTRANT -g -Isfwl -c sfwl/core/socket.cpp -o sfwl/core/socket.o
ccache g++ -Wall -D_REENTRANT -g -Isfwl -c sfwl/core/inet_address.cpp -o sfwl/core/inet_address.o

ccache g++ -Wall -D_REENTRANT -g -Isfwl -c sfwl/core/sub_process.cpp -o sfwl/core/sub_process.o

ccache g++ -Wall -D_REENTRANT -g -Isfwl -c sfwl/core/sfw_core.cpp -o sfwl/core/sfw_core.o

ccache g++ -Wall -D_REENTRANT -g -Isfwl -c sfwl/core/os.cpp -o sfwl/core/os.o

ccache g++ -Wall -D_REENTRANT -g -Isfwl -c sfwl/object/object.cpp -o sfwl/object/object.o
ccache g++ -Wall -D_REENTRANT -g -Isfwl -c sfwl/object/reference.cpp -o sfwl/object/reference.o
ccache g++ -Wall -D_REENTRANT -g -Isfwl -c sfwl/object/core_string_names.cpp -o sfwl/object/core_string_names.o
ccache g++ -Wall -D_REENTRANT -g -Isfwl -c sfwl/object/variant.cpp -o sfwl/object/variant.o
ccache g++ -Wall -D_REENTRANT -g -Isfwl -c sfwl/object/variant_op.cpp -o sfwl/object/variant_op.o
ccache g++ -Wall -D_REENTRANT -g -Isfwl -c sfwl/object/psignal.cpp -o sfwl/object/psignal.o
ccache g++ -Wall -D_REENTRANT -g -Isfwl -c sfwl/object/array.cpp -o sfwl/object/array.o
ccache g++ -Wall -D_REENTRANT -g -Isfwl -c sfwl/object/dictionary.cpp -o sfwl/object/dictionary.o
ccache g++ -Wall -D_REENTRANT -g -Isfwl -c sfwl/object/ref_ptr.cpp -o sfwl/object/ref_ptr.o
ccache g++ -Wall -D_REENTRANT -g -Isfwl -c sfwl/object/resource.cpp -o sfwl/object/resource.o

ccache g++ -Wall -D_REENTRANT -g -Isfwl -c sfwl/main.cpp -o sfwl/main.o

# You might need to add -lpthread and/or -latomic depending on your compiler version  (add it near -lX11)

ccache g++ -Wall -D_REENTRANT -g  sfwl/core/color.o sfwl/core/rect2i.o sfwl/core/vector2i.o \
                        sfwl/core/logger.o sfwl/core/math_funcs.o \
                        sfwl/core/memory.o sfwl/core/pcg.o sfwl/core/random_pcg.o \
                        sfwl/core/safe_refcount.o \
                        sfwl/core/ustring.o sfwl/core/string_name.o \
                        sfwl/core/pool_vector.o sfwl/core/pool_allocator.o sfwl/core/mutex.o sfwl/core/sfw_time.o \
												sfwl/core/rw_lock.o sfwl/core/semaphore.o \
												sfwl/core/string_builder.o \
                        sfwl/core/dir_access.o sfwl/core/file_access.o sfwl/core/thread.o \
                        sfwl/core/socket.o sfwl/core/inet_address.o \
                        sfwl/core/sub_process.o \
                        sfwl/core/sfw_core.o \
                        sfwl/core/os.o \
                        sfwl/object/object.o sfwl/object/reference.o sfwl/object/core_string_names.o \
                        sfwl/object/variant.o sfwl/object/variant_op.o sfwl/object/psignal.o \
                        sfwl/object/array.o sfwl/object/dictionary.o sfwl/object/ref_ptr.o \
                        sfwl/object/resource.o \
                        sfwl/main.o \
                        -o sfwl_app 

