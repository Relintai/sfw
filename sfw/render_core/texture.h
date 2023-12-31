#ifndef TEXTURE_H
#define TEXTURE_H

#include "3rd_glad.h"
#include "image.h"

class Texture {
public:
	enum TextureFlags {
		TEXTURE_FLAG_FILTER = 1 << 0,
		TEXTURE_FLAG_REPEAT = 1 << 1,
		TEXTURE_FLAG_MIRRORED_REPEAT = 1 << 2,
		TEXTURE_FLAG_MIP_MAPS = 1 << 3,
	};

	_FORCE_INLINE_ GLuint get_gl_texture() {
		return _texture;
	}

	void set_as_render_target();
	void unset_render_target();

	void create_from_image(const Ref<Image> &img);

	Ref<Image> get_data();

	void upload();

	Texture();
	virtual ~Texture();

protected:
	void _get_gl_format(Image::Format p_format, GLenum &r_gl_format, GLenum &r_gl_internal_format, GLenum &r_gl_type, bool &r_supported) const;

	Ref<Image> _image;

	int _texture_width;
	int _texture_height;
	Image::Format _texture_format;

	int _flags;
	int _texture_index;
	int _data_size;
	int _mipmaps;

	GLuint _texture;

	int _fbo_width;
	int _fbo_height;
	GLuint _fbo;
};

#endif // TEXTURE_H
