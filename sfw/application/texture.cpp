#include "texture.h"

#include "memory.h"
#include <stdio.h>

#define STB_IMAGE_IMPLEMENTATION // stbi
#define STB_IMAGE_WRITE_IMPLEMENTATION // stbi_write
#define STB_SPRINTF_IMPLEMENTATION // stb_sprintf
#define STB_SPRINTF_NOUNALIGNED // stb_sprintf

#include "3rd_stb_image.h"

//{{FILE:3rd_stb_image_write.h}}
//---
#undef freelist
#define STBTT_malloc(x, u) ((void)(u), MALLOC(x))
#define STBTT_free(x, u) ((void)(u), FREE(x))
#define NK_ASSERT ASSERT
#define NK_DTOA(s, n) strcpy(s, va("%f", n)) // override cos built-in nk_dtoa() will freeze while parsing UINT_MAX otherwise

void Texture::image_data_load(const char *file_name, int flags) {
	//stbi_set_flip_vertically_on_load(flags & IMAGE_FLIP ? 1 : 0);

	int img_n = 0;
	//if (flags & IMAGE_R)
	//	n = 1;
	//if (flags & IMAGE_RG)
	//	n = 2;
	//if (flags & IMAGE_RGB)
	//	n = 3;
	//if (flags & IMAGE_RGBA)
	img_n = 4;
	//if (flags & IMAGE_FLOAT)
	//	img.pixels = stbi_loadf_from_file((const stbi_uc *)data, size, (int *)&img.x, (int *)&img.y, (int *)&img.n, n);
	//else

	FILE *fp = fopen(file_name, "r");

	pixels = stbi_load_from_file(fp, &x, &y, &n, img_n);

	fclose(fp);

	//if (img.pixels) {
	//	PRINTF("Loaded image (%dx%d %.*s->%.*s)\n", img.w, img.h, img.n, "RGBA", n ? n : img.n, "RGBA");
	//} else {
	// PANIC("Error loading image (%s)\n", pathfile);
	//}

	n = img_n ? img_n : n;
}

void Texture::load_image(const char *file_name, const int format, const int internal_components) {
	if (pixels) {
        //TODO
		//memdelete(pixels);
		pixels = NULL;
		glDeleteTextures(1, &texture);
	}

	image_data_load(file_name, 0);

	if (!pixels) {
		printf("Couldn't load %s.\n", file_name);
	} else {
		//image = SDL_ConvertSurfaceFormat(img, SDL_PIXELFORMAT_RGBA32, 0);
		//SDL_FreeSurface(img);

		glGenTextures(1, &texture);

        texture_update(0);

		//glBindTexture(GL_TEXTURE_2D, texture);
		//glTexImage2D(GL_TEXTURE_2D, 0, format, image->w, image->h, 0, internal_components, GL_UNSIGNED_BYTE, image->pixels);
		//apply_filter();
	}
}

void Texture::texture_update(int flags) {
	if (!pixels) {
		return;
	}

	//if (t && !t->id) {
	//	glGenTextures(1, &t->id);
	//	return texture_update(t, w, h, n, pixels, flags);
	//}

	//ASSERT(t && t->id);
	//ASSERT(n <= 4);

	//GLuint pixel_types[] = { GL_RED, GL_RED, GL_RG, GL_RGB, GL_RGBA, GL_R32F, GL_R32F, GL_RG32F, GL_RGB32F, GL_RGBA32F };
	//GLenum pixel_storage = flags & TEXTURE_FLOAT ? GL_FLOAT : GL_UNSIGNED_BYTE;
	GLenum pixel_storage = GL_UNSIGNED_BYTE;
	//GLuint pixel_type = pixel_types[n];
    GLuint pixel_type = GL_RGBA;
	//GLuint texel_type = t->texel_type = pixel_types[n + 5 * !!(flags & TEXTURE_FLOAT)];
    GLuint texel_type = GL_RGBA;
	GLenum wrap = GL_CLAMP_TO_EDGE;
	GLenum min_filter = GL_NEAREST, mag_filter = GL_NEAREST;
	//    GLfloat color = (flags&7)/7.f, border_color[4] = { color, color, color, 1.f };

    /*
	if (flags & TEXTURE_BGR)
		if (pixel_type == GL_RGB)
			pixel_type = GL_BGR;
	if (flags & TEXTURE_BGR)
		if (pixel_type == GL_RGBA)
			pixel_type = GL_BGRA;
	if (flags & TEXTURE_SRGB)
		if (texel_type == GL_RGB)
			texel_type = GL_SRGB;
	if (flags & TEXTURE_SRGB)
		if (texel_type == GL_RGBA)
			texel_type = GL_SRGB_ALPHA; // GL_SRGB8_ALPHA8 ?
            */
    /*
	if (flags & TEXTURE_BC1)
		texel_type = GL_COMPRESSED_RGBA_S3TC_DXT1_EXT;
	if (flags & TEXTURE_BC2)
		texel_type = GL_COMPRESSED_RGBA_S3TC_DXT3_EXT;
	if (flags & TEXTURE_BC3)
		texel_type = GL_COMPRESSED_RGBA_S3TC_DXT5_EXT;
	if (flags & TEXTURE_DEPTH)
		texel_type = pixel_type = GL_DEPTH_COMPONENT; // GL_DEPTH_COMPONENT32

	if (flags & TEXTURE_REPEAT)
		wrap = GL_REPEAT;
	if (flags & TEXTURE_BORDER)
		wrap = GL_CLAMP_TO_BORDER;
	if (flags & TEXTURE_LINEAR)
		min_filter = GL_LINEAR, mag_filter = GL_LINEAR;
	if (flags & TEXTURE_MIPMAPS)
		min_filter = flags & TEXTURE_LINEAR ? GL_LINEAR_MIPMAP_LINEAR : GL_NEAREST_MIPMAP_LINEAR; // : GL_LINEAR_MIPMAP_NEAREST; maybe?
	if (flags & TEXTURE_MIPMAPS)
		mag_filter = flags & TEXTURE_LINEAR ? GL_LINEAR : GL_NEAREST;
        */

#if 0
    if( 0 ) { // flags & TEXTURE_PREMULTIPLY_ALPHA )
        uint8_t *p = pixels;
        if(n == 2) for( unsigned i = 0; i < 2*w*h; i += 2 ) {
            p[i] = (p[i] * p[i+1] + 128) >> 8;
        }
        if(n == 4) for( unsigned i = 0; i < 4*w*h; i += 4 ) {
            p[i+0] = (p[i+0] * p[i+3] + 128) >> 8;
            p[i+1] = (p[i+1] * p[i+3] + 128) >> 8;
            p[i+2] = (p[i+2] * p[i+3] + 128) >> 8;
        }
    }
#endif

	//GLenum texture_type = t->flags & TEXTURE_ARRAY ? GL_TEXTURE_2D_ARRAY : GL_TEXTURE_2D; // @fixme: test GL_TEXTURE_2D_ARRAY
    GLenum texture_type = GL_TEXTURE_2D; // @fixme: test GL_TEXTURE_2D_ARRAY

	//glPixelStorei( GL_UNPACK_ALIGNMENT, n < 4 ? 1 : 4 ); // for framebuffer reading
	//glActiveTexture(GL_TEXTURE0 + (flags&7));
	glBindTexture(texture_type, texture);
	glTexImage2D(texture_type, 0, texel_type, w, h, 0, pixel_type, pixel_storage, pixels);
	glTexParameteri(texture_type, GL_TEXTURE_WRAP_S, wrap);
	glTexParameteri(texture_type, GL_TEXTURE_WRAP_T, wrap);
	glTexParameteri(texture_type, GL_TEXTURE_MIN_FILTER, min_filter);
	glTexParameteri(texture_type, GL_TEXTURE_MAG_FILTER, mag_filter);
#if 0 // only for sampler2DShadow
    if( flags & TEXTURE_DEPTH )   glTexParameteri(texture_type, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_REF_TO_TEXTURE);
    if( flags & TEXTURE_DEPTH )   glTexParameteri(texture_type, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL);
#endif
	//  if( flags & TEXTURE_BORDER )  glTexParameterfv(texture_type, GL_TEXTURE_BORDER_COLOR, border_color);
    /*
	if (flags & TEXTURE_MIPMAPS)
		glGenerateMipmap(texture_type);

	if (flags & TEXTURE_MIPMAPS) {
		GLfloat max_aniso = 0;
		//        glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY, &max_aniso);
		max_aniso = 4;
		//        glTexParameterf(texture_type, GL_TEXTURE_MAX_ANISOTROPY, max_aniso);
	}

    */

	// glBindTexture(texture_type, 0); // do not unbind. current code expects texture to be bound at function exit
    /*
	t->w = w;
	t->h = h;
	t->n = n;
	t->flags = flags;
	t->filename = t->filename ? t->filename : "";
    */
}

void Texture::apply_filter() {
	GLint params = GL_NEAREST;

	if (filter == TEXTURE_FILTER_LINEAR) {
		params = GL_LINEAR;
	}

	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, params);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, params);
}

Texture::Texture() {
	filter = TEXTURE_FILTER_NEAREST;
	texture = 0;
	pixels = NULL;
}

Texture::~Texture() {
	if (pixels) {
        //todo
		//delete (pixels);

		glDeleteTextures(1, &texture);
	}
}
