

#define GLAD_GL_IMPLEMENTATION // glad
#include "render_core/3rd_glad.h"

#define _GLFW_IMPLEMENTATION // glfw337
#define GLFW_INCLUDE_NONE // glfw337

#define _GLFW_COCOA // glfw osx

#undef _GNU_SOURCE

#include "3rd_glfw3.h"
#undef timeGetTime
#undef Time
