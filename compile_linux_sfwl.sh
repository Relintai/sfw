

# You might need to add -std=c++14 depending on your compiler version

ccache g++ -Wall -D_REENTRANT -g -Isfw -c sfw/core/aabb.cpp -o sfw/core/aabb.o
ccache g++ -Wall -D_REENTRANT -g -Isfw -c sfw/core/basis.cpp -o sfw/core/basis.o
ccache g++ -Wall -D_REENTRANT -g -Isfw -c sfw/core/color.cpp -o sfw/core/color.o
ccache g++ -Wall -D_REENTRANT -g -Isfw -c sfw/core/face3.cpp -o sfw/core/face3.o
ccache g++ -Wall -D_REENTRANT -g -Isfw -c sfw/core/logger.cpp -o sfw/core/logger.o
ccache g++ -Wall -D_REENTRANT -g -Isfw -c sfw/core/math_funcs.cpp -o sfw/core/math_funcs.o
ccache g++ -Wall -D_REENTRANT -g -Isfw -c sfw/core/memory.cpp -o sfw/core/memory.o
ccache g++ -Wall -D_REENTRANT -g -Isfw -c sfw/core/pcg.cpp -o sfw/core/pcg.o
ccache g++ -Wall -D_REENTRANT -g -Isfw -c sfw/core/plane.cpp -o sfw/core/plane.o
ccache g++ -Wall -D_REENTRANT -g -Isfw -c sfw/core/projection.cpp -o sfw/core/projection.o
ccache g++ -Wall -D_REENTRANT -g -Isfw -c sfw/core/quaternion.cpp -o sfw/core/quaternion.o
ccache g++ -Wall -D_REENTRANT -g -Isfw -c sfw/core/random_pcg.cpp -o sfw/core/random_pcg.o
ccache g++ -Wall -D_REENTRANT -g -Isfw -c sfw/core/rect2.cpp -o sfw/core/rect2.o
ccache g++ -Wall -D_REENTRANT -g -Isfw -c sfw/core/rect2i.cpp -o sfw/core/rect2i.o
ccache g++ -Wall -D_REENTRANT -g -Isfw -c sfw/core/safe_refcount.cpp -o sfw/core/safe_refcount.o
ccache g++ -Wall -D_REENTRANT -g -Isfw -c sfw/core/transform_2d.cpp -o sfw/core/transform_2d.o
ccache g++ -Wall -D_REENTRANT -g -Isfw -c sfw/core/transform.cpp -o sfw/core/transform.o
ccache g++ -Wall -D_REENTRANT -g -Isfw -c sfw/core/ustring.cpp -o sfw/core/ustring.o
ccache g++ -Wall -D_REENTRANT -g -Isfw -c sfw/core/string_name.cpp -o sfw/core/string_name.o
ccache g++ -Wall -D_REENTRANT -g -Isfw -c sfw/core/vector2.cpp -o sfw/core/vector2.o
ccache g++ -Wall -D_REENTRANT -g -Isfw -c sfw/core/vector2i.cpp -o sfw/core/vector2i.o
ccache g++ -Wall -D_REENTRANT -g -Isfw -c sfw/core/vector3.cpp -o sfw/core/vector3.o
ccache g++ -Wall -D_REENTRANT -g -Isfw -c sfw/core/vector3i.cpp -o sfw/core/vector3i.o
ccache g++ -Wall -D_REENTRANT -g -Isfw -c sfw/core/vector4.cpp -o sfw/core/vector4.o
ccache g++ -Wall -D_REENTRANT -g -Isfw -c sfw/core/vector4i.cpp -o sfw/core/vector4i.o

ccache g++ -Wall -D_REENTRANT -g -Isfw -c sfw/core/file_access.cpp -o sfw/core/file_access.o
ccache g++ -Wall -D_REENTRANT -g -Isfw -c sfw/core/dir_access.cpp -o sfw/core/dir_access.o

ccache g++ -Wall -D_REENTRANT -g -Isfw -c sfw/core/pool_vector.cpp -o sfw/core/pool_vector.o
ccache g++ -Wall -D_REENTRANT -g -Isfw -c sfw/core/pool_allocator.cpp -o sfw/core/pool_allocator.o
ccache g++ -Wall -D_REENTRANT -g -Isfw -c sfw/core/mutex.cpp -o sfw/core/mutex.o
ccache g++ -Wall -D_REENTRANT -g -Isfw -c sfw/core/sfw_time.cpp -o sfw/core/sfw_time.o

ccache g++ -Wall -D_REENTRANT -g -Isfw -c sfw/core/thread.cpp -o sfw/core/thread.o
ccache g++ -Wall -D_REENTRANT -g -Isfw -c sfw/core/socket.cpp -o sfw/core/socket.o
ccache g++ -Wall -D_REENTRANT -g -Isfw -c sfw/core/inet_address.cpp -o sfw/core/inet_address.o

ccache g++ -Wall -D_REENTRANT -g -Isfw -c sfw/core/sub_process.cpp -o sfw/core/sub_process.o

ccache g++ -Wall -D_REENTRANT -g -Isfw -c sfw/core/sfw_core.cpp -o sfw/core/sfw_core.o

ccache g++ -Wall -D_REENTRANT -g -Isfw -c sfw/object/object.cpp -o sfw/object/object.o
ccache g++ -Wall -D_REENTRANT -g -Isfw -c sfw/object/reference.cpp -o sfw/object/reference.o
ccache g++ -Wall -D_REENTRANT -g -Isfw -c sfw/object/core_string_names.cpp -o sfw/object/core_string_names.o
ccache g++ -Wall -D_REENTRANT -g -Isfw -c sfw/object/variant.cpp -o sfw/object/variant.o
ccache g++ -Wall -D_REENTRANT -g -Isfw -c sfw/object/variant_op.cpp -o sfw/object/variant_op.o
ccache g++ -Wall -D_REENTRANT -g -Isfw -c sfw/object/psignal.cpp -o sfw/object/psignal.o
ccache g++ -Wall -D_REENTRANT -g -Isfw -c sfw/object/array.cpp -o sfw/object/array.o
ccache g++ -Wall -D_REENTRANT -g -Isfw -c sfw/object/dictionary.cpp -o sfw/object/dictionary.o
ccache g++ -Wall -D_REENTRANT -g -Isfw -c sfw/object/ref_ptr.cpp -o sfw/object/ref_ptr.o
ccache g++ -Wall -D_REENTRANT -g -Isfw -c sfw/object/resource.cpp -o sfw/object/resource.o

ccache g++ -Wall -D_REENTRANT -g -Isfw -c sfw/main.cpp -o sfw/main.o

# You might need to add -lpthread and/or -latomic depending on your compiler version  (add it near -lX11)

ccache g++ -Wall -D_REENTRANT -g sfw/core/aabb.o sfw/core/basis.o sfw/core/color.o \
                        sfw/core/face3.o sfw/core/logger.o sfw/core/math_funcs.o \
                        sfw/core/memory.o sfw/core/pcg.o sfw/core/plane.o sfw/core/projection.o sfw/core/quaternion.o sfw/core/random_pcg.o \
                        sfw/core/rect2.o sfw/core/rect2i.o sfw/core/safe_refcount.o sfw/core/transform_2d.o sfw/core/transform.o \
                        sfw/core/ustring.o sfw/core/string_name.o \
                        sfw/core/vector2.o sfw/core/vector2i.o sfw/core/vector3.o \
                        sfw/core/vector3i.o sfw/core/vector4.o sfw/core/vector4i.o \
                        sfw/core/pool_vector.o sfw/core/pool_allocator.o sfw/core/mutex.o sfw/core/sfw_time.o \
                        sfw/core/dir_access.o sfw/core/file_access.o sfw/core/thread.o \
                        sfw/core/socket.o sfw/core/inet_address.o \
                        sfw/core/sub_process.o \
                        sfw/core/sfw_core.o \
                        sfw/object/object.o sfw/object/reference.o sfw/object/core_string_names.o \
                        sfw/object/variant.o sfw/object/variant_op.o sfw/object/psignal.o \
                        sfw/object/array.o sfw/object/dictionary.o sfw/object/ref_ptr.o \
                        sfw/object/resource.o \
                        sfw/main.o \
                        -o sfwl_app 
