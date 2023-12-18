#ifndef OPENGL_H
#define OPENGL_H

#if defined(__unix__) && !defined(__ANDROID__)
#define GL_GLEXT_PROTOTYPES
#include <GL/gl.h>
#endif // __unix__

#if __ANDROID__
#define GL_GLEXT_PROTOTYPES
#include <GLES2/gl2.h>
#endif

#if defined(_WIN64) || defined(_WIN32)
#include "3rd_glad.h"
#endif // defined

#endif // OPENGL_H
