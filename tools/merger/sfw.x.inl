
// https://github.com/Relintai/sfw

/*
Copyright (c) 2023-present Péter Magyar.

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

// TODO gather all licenses to here



#ifdef SFW_3RD_H
#endif

//Add implementation defines


#define GLAD_GL_IMPLEMENTATION // glad
{{FILE:sfw/render_core/3rd_glad.h}}

#define STB_TRUETYPE_IMPLEMENTATION
{{FILE:sfw/render_core/3rd_stb_truetype.h}}



#define STB_IMAGE_IMPLEMENTATION // stbi
#define STB_IMAGE_WRITE_IMPLEMENTATION // stbi_write
#define STB_SPRINTF_IMPLEMENTATION // stb_sprintf
#define STB_SPRINTF_NOUNALIGNED // stb_sprintf

{{FILE:sfw/render_core/3rd_stb_image.h}}

//{//{//FILE:sfw/render_core/stb_image_write.h}}
//---
#undef freelist
//#define STBTT_malloc(x, u) ((void)(u), MALLOC(x))
//#define STBTT_free(x, u) ((void)(u), FREE(x))
//#define NK_ASSERT ASSERT
//#define NK_DTOA(s, n) strcpy(s, va("%f", n)) // override cos built-in nk_dtoa() will freeze while parsing UINT_MAX otherwise


#define _GLFW_IMPLEMENTATION // glfw337
#define GLFW_INCLUDE_NONE // glfw337
#ifdef __APPLE__
#define _GLFW_COCOA // glfw osx
#elif defined(_WIN32) || defined(_WIN64)
#define _GLFW_WIN32 // glfw win32
#else
#define _GLFW_X11 // glfw linux, also _GLFW_OSMESA or _GLFW_WAYLAND
#endif

#undef _GNU_SOURCE

{{FILE:sfw/render_core/3rd_glfw3.h}}

#undef timeGetTime
#undef Time
