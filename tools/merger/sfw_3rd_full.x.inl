

{{FILEINLINE:tools/merger/sfw_readme.inl.h}}
{{FILEINLINE:tools/merger/sfw_linceses_core.inl.h}}
{{FILEINLINE:tools/merger/sfw_linceses_render_core.inl.h}}

#ifdef SFW_3RD_IMPL
#define GLAD_GL_IMPLEMENTATION // glad
#endif

{{FILE:sfw/render_core/3rd_glad.h}}

#ifdef SFW_3RD_IMPL
#define STB_TRUETYPE_IMPLEMENTATION

{{FILE:sfw/render_core/3rd_stb_truetype.h}}

#define STB_IMAGE_IMPLEMENTATION // stbi
#define STB_IMAGE_WRITE_IMPLEMENTATION // stbi_write
#define STB_SPRINTF_IMPLEMENTATION // stb_sprintf
#define STB_SPRINTF_NOUNALIGNED // stb_sprintf

{{FILE:sfw/render_core/3rd_stb_image.h}}

{{FILE:sfw/render_core/3rd_stb_image_write.h}}

//---
#undef freelist

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

#endif
