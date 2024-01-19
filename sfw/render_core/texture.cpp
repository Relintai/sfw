//--STRIP
#include "render_core/texture.h"

#include "core/memory.h"
#include <stdio.h>

#include "render_core/app_window.h"

#include "render_core/frame_buffer.h"
//--STRIP

void Texture::create_from_image(const Ref<Image> &img) {
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

	upload();
}

Ref<Image> Texture::get_data() {
	ERR_FAIL_COND_V(!_texture, Ref<Image>());
	ERR_FAIL_COND_V(_data_size == 0, Ref<Image>());

	//GLES

	uint32_t gl_format;
	uint32_t gl_internal_format;
	uint32_t gl_type;
	bool supported;
	_get_gl_format(_texture_format, gl_format, gl_internal_format, gl_type, supported);

	if (!supported) {
		return Ref<Image>();
	}

	Vector<uint8_t> data;

	int data_size = Image::get_image_data_size(_texture_width, _texture_height, _texture_format, _mipmaps > 1);

	data.resize(data_size * 2); //add some memory at the end, just in case for buggy drivers
	uint8_t *wb = data.ptrw();

	glActiveTexture(GL_TEXTURE0);

	glBindTexture(GL_TEXTURE_2D, _texture);
	glBindBuffer(GL_PIXEL_PACK_BUFFER, 0);

	for (int i = 0; i < _mipmaps; i++) {
		int ofs = Image::get_image_mipmap_offset(_texture_width, _texture_height, _texture_format, i);

		glPixelStorei(GL_PACK_ALIGNMENT, 1);
		glGetTexImage(GL_TEXTURE_2D, i, gl_format, gl_type, &wb[ofs]);
	}

	data.resize(data_size);

	Image *img = memnew(Image(_texture_width, _texture_height, _mipmaps > 1, _texture_format, data));

	return Ref<Image>(img);
}

Vector2i Texture::get_size() const {
	return Vector2i(_texture_width, _texture_height);
}

void Texture::upload() {
	if (!_image.is_valid()) {
		return;
	}

	uint32_t gl_format;
	uint32_t gl_internal_format;
	uint32_t gl_type;
	bool supported;
	Image::Format image_format = _image->get_format();
	_get_gl_format(image_format, gl_format, gl_internal_format, gl_type, supported);

	if (!supported) {
		return;
	}

	_data_size = _image->get_data().size();
	_texture_format = image_format;
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

	uint32_t texture_type = GL_TEXTURE_2D;

	glBindTexture(texture_type, _texture);

	int mipmaps = ((_flags & TEXTURE_FLAG_MIP_MAPS) && _image->has_mipmaps()) ? _image->get_mipmap_count() + 1 : 1;

	if (mipmaps > 1) {
		if ((_flags & TEXTURE_FLAG_FILTER)) {
			glTexParameteri(texture_type, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		} else {
			glTexParameteri(texture_type, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
		}
	} else {
		if ((_flags & TEXTURE_FLAG_FILTER)) {
			glTexParameteri(texture_type, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		} else {
			glTexParameteri(texture_type, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		}
	}

	if ((_flags & TEXTURE_FLAG_FILTER)) {
		glTexParameteri(texture_type, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // Linear Filtering
	} else {
		glTexParameteri(texture_type, GL_TEXTURE_MAG_FILTER, GL_NEAREST); // raw Filtering
	}

	if ((_flags & TEXTURE_FLAG_REPEAT) || (_flags & TEXTURE_FLAG_MIRRORED_REPEAT)) {
		if (_flags & TEXTURE_FLAG_MIRRORED_REPEAT) {
			glTexParameterf(texture_type, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
			glTexParameterf(texture_type, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
		} else {
			glTexParameterf(texture_type, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameterf(texture_type, GL_TEXTURE_WRAP_T, GL_REPEAT);
		}
	} else {
		glTexParameterf(texture_type, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameterf(texture_type, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	}

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

	if (mipmaps > 1) {
		//generate mipmaps if they were requested and the image does not contain them
		glGenerateMipmap(texture_type);
	}

	_mipmaps = mipmaps;

	glBindTexture(texture_type, 0);
}

void Texture::_get_gl_format(Image::Format p_format, uint32_t &r_gl_format, uint32_t &r_gl_internal_format, uint32_t &r_gl_type, bool &r_supported) const {
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

Texture::Texture() {
	_texture = 0;
	_texture_width = 0;
	_texture_height = 0;
	_mipmaps = 1;
	_data_size = 0;
	_texture_index = 0;
	_flags = 0;

	_texture_format = Image::FORMAT_RGBA8;
}

Texture::~Texture() {
	if (_texture) {
		glDeleteTextures(1, &_texture);
	}
}

//RenderTexture

bool RenderTexture::get_v_flip() const {
	return _v_flip;
}
void RenderTexture::set_v_flip(const bool p_v_flip) {
	_v_flip = p_v_flip;
}

RenderTexture::RenderTextureType RenderTexture::get_type() const {
	return _type;
}
void RenderTexture::set_type(const RenderTextureType p_type) {
	_type = p_type;
}

Ref<FrameBuffer> RenderTexture::get_frame_buffer() const {
	return _frame_buffer;
}
void RenderTexture::set_frame_buffer(const Ref<FrameBuffer> &p_frame_buffer) {
	_frame_buffer = p_frame_buffer;
}

void RenderTexture::update() {
	if (!_frame_buffer.is_valid()) {
		return;
	}

	_frame_buffer->update();

	Ref<Image> img;

	switch (_type) {
		case RENDER_TEXTURE_TYPE_COLOR:
			img = _frame_buffer->get_image_color();

			if (_v_flip) {
				img->flip_y();
			}

			create_from_image(img);

			break;
		case RENDER_TEXTURE_TYPE_DEPTH:
			img = _frame_buffer->get_image_depth();

			if (_v_flip) {
				img->flip_y();
			}

			create_from_image(img);

			break;
		default:
			break;
	}
}

RenderTexture::RenderTexture() {
	_type = RENDER_TEXTURE_TYPE_COLOR;
	_v_flip = true;
}

RenderTexture::~RenderTexture() {
	_frame_buffer.unref();
}
