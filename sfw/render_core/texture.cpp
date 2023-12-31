#include "texture.h"

#include "memory.h"
#include <stdio.h>

void Texture::_get_gl_and_format(Image::Format p_format, GLenum &r_gl_format, GLenum &r_gl_internal_format, GLenum &r_gl_type, bool &r_supported) const {
	r_gl_format = 0;
	r_supported = true;

	switch (p_format) {
		case Image::FORMAT_L8: {
			r_gl_internal_format = GL_LUMINANCE;
			r_gl_format = GL_LUMINANCE;
			r_gl_type = GL_UNSIGNED_BYTE;
		} break;
		case Image::FORMAT_LA8: {
			r_gl_internal_format = GL_LUMINANCE_ALPHA;
			r_gl_format = GL_LUMINANCE_ALPHA;
			r_gl_type = GL_UNSIGNED_BYTE;
		} break;
		case Image::FORMAT_R8: {
			r_gl_internal_format = GL_ALPHA;
			r_gl_format = GL_ALPHA;
			r_gl_type = GL_UNSIGNED_BYTE;

		} break;
		case Image::FORMAT_RG8: {
			ERR_PRINT("RG texture not supported! Convert it to to RGB8.");

			r_supported = false;
		} break;
		case Image::FORMAT_RGB8: {
			r_gl_internal_format = GL_RGB;
			r_gl_format = GL_RGB;
			r_gl_type = GL_UNSIGNED_BYTE;

		} break;
		case Image::FORMAT_RGBA8: {
			r_gl_format = GL_RGBA;
			r_gl_internal_format = GL_RGBA;
			r_gl_type = GL_UNSIGNED_BYTE;

		} break;
		case Image::FORMAT_RGBA4444: {
			r_gl_internal_format = GL_RGBA;
			r_gl_format = GL_RGBA;
			r_gl_type = GL_UNSIGNED_SHORT_4_4_4_4;

		} break;
		case Image::FORMAT_RGBA5551: {
			r_gl_internal_format = GL_RGB5_A1;
			r_gl_format = GL_RGBA;
			r_gl_type = GL_UNSIGNED_SHORT_5_5_5_1;

		} break;
		case Image::FORMAT_RF: {
			r_gl_internal_format = GL_ALPHA;
			r_gl_format = GL_ALPHA;
			r_gl_type = GL_FLOAT;
		} break;
		case Image::FORMAT_RGF: {
			ERR_PRINT("RG float texture not supported! Convert it to RGB8.");
			r_supported = false;
		} break;
		case Image::FORMAT_RGBF: {
			r_gl_internal_format = GL_RGB;
			r_gl_format = GL_RGB;
			r_gl_type = GL_FLOAT;
		} break;
		case Image::FORMAT_RGBAF: {
			r_gl_internal_format = GL_RGBA;
			r_gl_format = GL_RGBA;
			r_gl_type = GL_FLOAT;
		} break;
		default: {
			r_supported = false;
			ERR_FAIL_COND(true);
		}
	}
}

void Texture::texture_update() {
	if (!_image.is_valid()) {
		return;
	}

	GLenum gl_format;
	GLenum gl_internal_format;
	GLenum gl_type;
	bool supported;
	_get_gl_and_format(_image->get_format(), gl_format, gl_internal_format, gl_type, supported);

	if (!supported) {
		return;
	}

	_data_size = _image->get_data().size();
	Vector<uint8_t> image_data = _image->get_data();

	if (image_data.size() == 0) {
		return;
	}

	const uint8_t *read = image_data.ptr();
	ERR_FAIL_COND(!read);

	if (!_texture) {
		glGenTextures(1, &_texture);
	}

	glActiveTexture(GL_TEXTURE0 + _texture_index);

	if ((_flags | TEXTURE_FLAG_MIP_MAPS)) {
		if ((_flags | TEXTURE_FLAG_FILTER)) {
			glTexParameteri(_texture, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		} else {
			glTexParameteri(_texture, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
		}
	} else {
		if ((_flags | TEXTURE_FLAG_FILTER)) {
			glTexParameteri(_texture, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		} else {
			glTexParameteri(_texture, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		}
	}

	if ((_flags | TEXTURE_FLAG_FILTER)) {
		glTexParameteri(_texture, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // Linear Filtering
	} else {
		glTexParameteri(_texture, GL_TEXTURE_MAG_FILTER, GL_NEAREST); // raw Filtering
	}

	if ((_flags & TEXTURE_FLAG_REPEAT) || (_flags & TEXTURE_FLAG_MIRRORED_REPEAT)) {
		if (_flags & TEXTURE_FLAG_MIRRORED_REPEAT) {
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
		} else {
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		}
	} else {
		glTexParameterf(_texture, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameterf(_texture, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	}

	GLenum texture_type = GL_TEXTURE_2D;

	glBindTexture(texture_type, _texture);

	int mipmaps = ((_flags | TEXTURE_FLAG_MIP_MAPS) && _image->has_mipmaps()) ? _image->get_mipmap_count() + 1 : 1;

	_texture_width = _image->get_width();
	_texture_height = _image->get_height();

	int w = _texture_width;
	int h = _texture_height;

	int tsize = 0;

	for (int i = 0; i < mipmaps; i++) {
		int size;
		int ofs;
		_image->get_mipmap_offset_and_size(i, ofs, size);

		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		glTexImage2D(texture_type, i, gl_internal_format, w, h, 0, gl_format, gl_type, &read[ofs]);

		tsize += size;

		w = MAX(1, w >> 1);
		h = MAX(1, h >> 1);
	}

	if ((_flags | TEXTURE_FLAG_MIP_MAPS) && mipmaps == 1) {
		//generate mipmaps if they were requested and the image does not contain them
		glGenerateMipmap(texture_type);
	}

	_mipmaps = mipmaps;

	glBindTexture(texture_type, 0);
}

void Texture::set_image(const Ref<Image> &img) {
	if (_image == img) {
		return;
	}

	_image = img;

	_texture_width = 0;
	_texture_height = 0;

	if (!_image.is_valid()) {
		if (_texture) {
			glDeleteTextures(1, &_texture);
			_texture = 0;
		}

		return;
	}

	texture_update();
}

Texture::Texture() {
	_texture = 0;
	_texture_width = 0;
	_texture_height = 0;
	_mipmaps = 1;
	_data_size = 0;
	_texture_index = 0;
	_flags = 0;
}

Texture::~Texture() {
	if (_texture) {
		glDeleteTextures(1, &_texture);
	}
}
