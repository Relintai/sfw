

{{FILEINLINE:tools/merger/sfw_readme.inl.h}}
{{FILEINLINE:tools/merger/sfw_linceses_core.inl.h}}
{{FILEINLINE:tools/merger/sfw_linceses_render_core.inl.h}}

// On OSX you need to compile this file separately with an objective c compiler

#ifndef ONLY_GLAD

#ifdef __APPLE__
#ifndef _APPLE_NO_IMPL_

#ifndef SFW_3RD_IMPL
#define SFW_3RD_IMPL
#endif //SFW_3RD_IMPL

#endif //_APPLE_NO_IMPL_
#endif //__APPLE__

#ifdef SFW_3RD_IMPL
#define GLAD_GL_IMPLEMENTATION // glad
#endif //SFW_3RD_IMPL

#endif //ONLY_GLAD

{{FILE:sfw/render_core/3rd_glad.h}}

#ifndef ONLY_GLAD

#ifdef SFW_3RD_IMPL
#define STB_TRUETYPE_IMPLEMENTATION
#define STB_RECT_PACK_IMPLEMENTATION
#define IMGUI_DISABLE_STB_RECT_PACK_IMPLEMENTATION
#endif //SFW_3RD_IMPL

{{FILE:sfw/render_gui/imstb_rectpack.h}}

{{FILE:sfw/render_core/3rd_stb_truetype.h}}

#ifdef SFW_3RD_IMPL
#define STB_IMAGE_IMPLEMENTATION // stbi
#define STB_IMAGE_WRITE_IMPLEMENTATION // stbi_write
#define STB_SPRINTF_IMPLEMENTATION // stb_sprintf
#define STB_SPRINTF_NOUNALIGNED // stb_sprintf
#endif //SFW_3RD_IMPL

{{FILE:sfw/render_core/3rd_stb_image.h}}

{{FILE:sfw/render_core/3rd_stb_image_write.h}}

//---
#undef freelist

#ifdef SFW_3RD_IMPL

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

#endif //SFW_3RD_IMPL

{{FILE:sfw/render_core/3rd_glfw3.h}}

#undef timeGetTime
#undef Time

#endif //ONLY_GLAD

