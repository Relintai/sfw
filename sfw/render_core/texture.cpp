#include "texture.h"

#include "memory.h"
#include <stdio.h>

/*
Ref<Image> RasterizerStorageGLES2::_get_gl_image_and_format(const Ref<Image> &p_image, Image::Format p_format, uint32_t p_flags, Image::Format &r_real_format, GLenum &r_gl_format, GLenum &r_gl_internal_format, GLenum &r_gl_type, bool &r_compressed, bool p_force_decompress) const {
	r_gl_format = 0;
	Ref<Image> image = p_image;
	r_compressed = false;
	r_real_format = p_format;

	bool need_decompress = false;

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
			ERR_PRINT("RG texture not supported, converting to RGB8.");
			if (image.is_valid()) {
				image->convert(Image::FORMAT_RGB8);
			}
			r_real_format = Image::FORMAT_RGB8;
			r_gl_internal_format = GL_RGB;
			r_gl_format = GL_RGB;
			r_gl_type = GL_UNSIGNED_BYTE;

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
			if (!config.float_texture_supported) {
				ERR_PRINT("R float texture not supported, converting to RGB8.");
				if (image.is_valid()) {
					image->convert(Image::FORMAT_RGB8);
				}
				r_real_format = Image::FORMAT_RGB8;
				r_gl_internal_format = GL_RGB;
				r_gl_format = GL_RGB;
				r_gl_type = GL_UNSIGNED_BYTE;
			} else {
				r_gl_internal_format = GL_ALPHA;
				r_gl_format = GL_ALPHA;
				r_gl_type = GL_FLOAT;
			}
		} break;
		case Image::FORMAT_RGF: {
			ERR_PRINT("RG float texture not supported, converting to RGB8.");
			if (image.is_valid()) {
				image->convert(Image::FORMAT_RGB8);
			}
			r_real_format = Image::FORMAT_RGB8;
			r_gl_internal_format = GL_RGB;
			r_gl_format = GL_RGB;
			r_gl_type = GL_UNSIGNED_BYTE;
		} break;
		case Image::FORMAT_RGBF: {
			if (!config.float_texture_supported) {
				ERR_PRINT("RGB float texture not supported, converting to RGB8.");
				if (image.is_valid()) {
					image->convert(Image::FORMAT_RGB8);
				}
				r_real_format = Image::FORMAT_RGB8;
				r_gl_internal_format = GL_RGB;
				r_gl_format = GL_RGB;
				r_gl_type = GL_UNSIGNED_BYTE;
			} else {
				r_gl_internal_format = GL_RGB;
				r_gl_format = GL_RGB;
				r_gl_type = GL_FLOAT;
			}
		} break;
		case Image::FORMAT_RGBAF: {
			if (!config.float_texture_supported) {
				ERR_PRINT("RGBA float texture not supported, converting to RGBA8.");
				if (image.is_valid()) {
					image->convert(Image::FORMAT_RGBA8);
				}
				r_real_format = Image::FORMAT_RGBA8;
				r_gl_internal_format = GL_RGBA;
				r_gl_format = GL_RGBA;
				r_gl_type = GL_UNSIGNED_BYTE;
			} else {
				r_gl_internal_format = GL_RGBA;
				r_gl_format = GL_RGBA;
				r_gl_type = GL_FLOAT;
			}
		} break;
		case Image::FORMAT_RH: {
			need_decompress = true;
		} break;
		case Image::FORMAT_RGH: {
			need_decompress = true;
		} break;
		case Image::FORMAT_RGBH: {
			need_decompress = true;
		} break;
		case Image::FORMAT_RGBAH: {
			need_decompress = true;
		} break;
		case Image::FORMAT_RGBE9995: {
			r_gl_internal_format = GL_RGB;
			r_gl_format = GL_RGB;
			r_gl_type = GL_UNSIGNED_BYTE;

			if (image.is_valid()) {
				image = image->rgbe_to_srgb();
			}

			return image;

		} break;
		case Image::FORMAT_DXT1: {
			if (config.s3tc_supported) {
				r_gl_internal_format = _EXT_COMPRESSED_RGBA_S3TC_DXT1_EXT;
				r_gl_format = GL_RGBA;
				r_gl_type = GL_UNSIGNED_BYTE;
				r_compressed = true;
			} else {
				need_decompress = true;
			}

		} break;
		case Image::FORMAT_DXT3: {
			if (config.s3tc_supported) {
				r_gl_internal_format = _EXT_COMPRESSED_RGBA_S3TC_DXT3_EXT;
				r_gl_format = GL_RGBA;
				r_gl_type = GL_UNSIGNED_BYTE;
				r_compressed = true;
			} else {
				need_decompress = true;
			}

		} break;
		case Image::FORMAT_DXT5: {
			if (config.s3tc_supported) {
				r_gl_internal_format = _EXT_COMPRESSED_RGBA_S3TC_DXT5_EXT;
				r_gl_format = GL_RGBA;
				r_gl_type = GL_UNSIGNED_BYTE;
				r_compressed = true;
			} else {
				need_decompress = true;
			}

		} break;
		case Image::FORMAT_RGTC_R: {
			if (config.rgtc_supported) {
				r_gl_internal_format = _EXT_COMPRESSED_RED_RGTC1_EXT;
				r_gl_format = GL_RGBA;
				r_gl_type = GL_UNSIGNED_BYTE;
				r_compressed = true;

			} else {
				need_decompress = true;
			}

		} break;
		case Image::FORMAT_RGTC_RG: {
			if (config.rgtc_supported) {
				r_gl_internal_format = _EXT_COMPRESSED_RED_GREEN_RGTC2_EXT;
				r_gl_format = GL_RGBA;
				r_gl_type = GL_UNSIGNED_BYTE;
				r_compressed = true;
			} else {
				need_decompress = true;
			}

		} break;
		case Image::FORMAT_BPTC_RGBA: {
			if (config.bptc_supported) {
				r_gl_internal_format = _EXT_COMPRESSED_RGBA_BPTC_UNORM;
				r_gl_format = GL_RGBA;
				r_gl_type = GL_UNSIGNED_BYTE;
				r_compressed = true;

			} else {
				need_decompress = true;
			}
		} break;
		case Image::FORMAT_BPTC_RGBF: {
			if (config.bptc_supported) {
				r_gl_internal_format = _EXT_COMPRESSED_RGB_BPTC_SIGNED_FLOAT;
				r_gl_format = GL_RGB;
				r_gl_type = GL_FLOAT;
				r_compressed = true;
			} else {
				need_decompress = true;
			}
		} break;
		case Image::FORMAT_BPTC_RGBFU: {
			if (config.bptc_supported) {
				r_gl_internal_format = _EXT_COMPRESSED_RGB_BPTC_UNSIGNED_FLOAT;
				r_gl_format = GL_RGB;
				r_gl_type = GL_FLOAT;
				r_compressed = true;
			} else {
				need_decompress = true;
			}
		} break;
		case Image::FORMAT_PVRTC2: {
			if (config.pvrtc_supported) {
				r_gl_internal_format = _EXT_COMPRESSED_RGB_PVRTC_2BPPV1_IMG;
				r_gl_format = GL_RGBA;
				r_gl_type = GL_UNSIGNED_BYTE;
				r_compressed = true;

			} else {
				need_decompress = true;
			}
		} break;
		case Image::FORMAT_PVRTC2A: {
			if (config.pvrtc_supported) {
				r_gl_internal_format = _EXT_COMPRESSED_RGBA_PVRTC_2BPPV1_IMG;
				r_gl_format = GL_RGBA;
				r_gl_type = GL_UNSIGNED_BYTE;
				r_compressed = true;

			} else {
				need_decompress = true;
			}

		} break;
		case Image::FORMAT_PVRTC4: {
			if (config.pvrtc_supported) {
				r_gl_internal_format = _EXT_COMPRESSED_RGB_PVRTC_4BPPV1_IMG;
				r_gl_format = GL_RGBA;
				r_gl_type = GL_UNSIGNED_BYTE;
				r_compressed = true;

			} else {
				need_decompress = true;
			}

		} break;
		case Image::FORMAT_PVRTC4A: {
			if (config.pvrtc_supported) {
				r_gl_internal_format = _EXT_COMPRESSED_RGBA_PVRTC_4BPPV1_IMG;
				r_gl_format = GL_RGBA;
				r_gl_type = GL_UNSIGNED_BYTE;
				r_compressed = true;

			} else {
				need_decompress = true;
			}

		} break;
		case Image::FORMAT_ETC: {
			if (config.etc1_supported) {
				r_gl_internal_format = _EXT_ETC1_RGB8_OES;
				r_gl_format = GL_RGBA;
				r_gl_type = GL_UNSIGNED_BYTE;
				r_compressed = true;
			} else {
				need_decompress = true;
			}
		} break;
		case Image::FORMAT_ETC2_R11: {
			need_decompress = true;
		} break;
		case Image::FORMAT_ETC2_R11S: {
			need_decompress = true;
		} break;
		case Image::FORMAT_ETC2_RG11: {
			need_decompress = true;
		} break;
		case Image::FORMAT_ETC2_RG11S: {
			need_decompress = true;
		} break;
		case Image::FORMAT_ETC2_RGB8: {
			need_decompress = true;
		} break;
		case Image::FORMAT_ETC2_RGBA8: {
			need_decompress = true;
		} break;
		case Image::FORMAT_ETC2_RGB8A1: {
			need_decompress = true;
		} break;
		default: {
			ERR_FAIL_V(Ref<Image>());
		}
	}

	if (need_decompress || p_force_decompress) {
		if (!image.is_null()) {
			image = image->duplicate();
			image->decompress();
			ERR_FAIL_COND_V(image->is_compressed(), image);
			switch (image->get_format()) {
				case Image::FORMAT_RGB8: {
					r_gl_format = GL_RGB;
					r_gl_internal_format = GL_RGB;
					r_gl_type = GL_UNSIGNED_BYTE;
					r_real_format = Image::FORMAT_RGB8;
					r_compressed = false;
				} break;
				case Image::FORMAT_RGBA8: {
					r_gl_format = GL_RGBA;
					r_gl_internal_format = GL_RGBA;
					r_gl_type = GL_UNSIGNED_BYTE;
					r_real_format = Image::FORMAT_RGBA8;
					r_compressed = false;
				} break;
				default: {
					image->convert(Image::FORMAT_RGBA8);
					r_gl_format = GL_RGBA;
					r_gl_internal_format = GL_RGBA;
					r_gl_type = GL_UNSIGNED_BYTE;
					r_real_format = Image::FORMAT_RGBA8;
					r_compressed = false;

				} break;
			}
		}

		return image;
	}

	return p_image;
}
*/

void Texture::texture_update() {
	if (!_image.is_valid()) {
		return;
	}

	//GLuint pixel_types[] = { GL_RED, GL_RED, GL_RG, GL_RGB, GL_RGBA, GL_R32F, GL_R32F, GL_RG32F, GL_RGB32F, GL_RGBA32F };
	//GLenum pixel_storage = flags & TEXTURE_FLOAT ? GL_FLOAT : GL_UNSIGNED_BYTE;
	GLenum pixel_storage = GL_UNSIGNED_BYTE;
	//GLuint pixel_type = pixel_types[n];
	GLuint pixel_type = GL_RGBA;
	//GLuint texel_type = t->texel_type = pixel_types[n + 5 * !!(flags & TEXTURE_FLOAT)];
	GLuint texel_type = GL_RGBA;

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

	_data_size = _image->get_data().size();
	Vector<uint8_t> image_data = _image->get_data();

	if (image_data.size() == 0) {
		return;
	}

	if (!_texture) {
		glGenTextures(1, &_texture);
	}

	const uint8_t *read = image_data.ptr();
	ERR_FAIL_COND(!read);

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
		glTexImage2D(texture_type, i, texel_type, w, h, 0, pixel_type, pixel_storage, &read[ofs]);

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
