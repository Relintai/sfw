//--STRIP
#include "render_core/frame_buffer.h"

#include "core/memory.h"
#include <stdio.h>

#include "render_core/app_window.h"
#include "render_core/render_state.h"
//--STRIP

int FrameBuffer::get_texture_flags() const {
	return _texture_flags;
}

void FrameBuffer::set_texture_flags(const int p_flags) {
	_texture_flags = p_flags;
}

int FrameBuffer::create(const int p_width, const int p_height, const int p_msaa_count) {
	ERR_FAIL_COND_V(p_width <= 0, -1);
	ERR_FAIL_COND_V(p_height <= 0, -1);
	ERR_FAIL_COND_V(p_msaa_count < 0, -1);

	int max_msaa_levels = 0;
	glGetIntegerv(GL_MAX_SAMPLES, &max_msaa_levels);

	int msaa = MIN(max_msaa_levels, p_msaa_count);

	if (msaa % 2 == 0) {
		--msaa;
	}
	
	destroy();

	_fbo_width = p_width;
	_fbo_height = p_height;
	_fbo_msaa_count = msaa;

	glGenFramebuffers(1, &_fbo);
	glBindFramebuffer(GL_FRAMEBUFFER, _fbo);

	glGenTextures(1, &_texture);
	glBindTexture(GL_TEXTURE_2D, _texture);

	if ((_texture_flags & FRAMEBUFFER_TEXTURE_FLAG_MIP_MAPS)) {
		if ((_texture_flags & FRAMEBUFFER_TEXTURE_FLAG_FILTER)) {
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		} else {
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
		}
	} else {
		if ((_texture_flags & FRAMEBUFFER_TEXTURE_FLAG_FILTER)) {
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		} else {
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		}
	}

	if ((_texture_flags & FRAMEBUFFER_TEXTURE_FLAG_FILTER)) {
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // Linear Filtering
	} else {
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST); // raw Filtering
	}

	if ((_texture_flags & FRAMEBUFFER_TEXTURE_FLAG_REPEAT) || (_texture_flags & FRAMEBUFFER_TEXTURE_FLAG_MIRRORED_REPEAT)) {
		if (_texture_flags & FRAMEBUFFER_TEXTURE_FLAG_MIRRORED_REPEAT) {
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
		} else {
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		}
	} else {
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	}

	glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, ((_texture_flags & FRAMEBUFFER_TEXTURE_FLAG_MIP_MAPS) > 0) ? GL_TRUE : GL_FALSE);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, _fbo_width, _fbo_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, _texture, 0);

	int status = get_status();

	if (status != GL_FRAMEBUFFER_COMPLETE) {
		glBindRenderbuffer(GL_RENDERBUFFER, 0);
		glBindTexture(GL_TEXTURE_2D, 0);
		glBindFramebuffer(GL_FRAMEBUFFER, 0);

		return status;
	}

	if (_fbo_msaa_count > 0) {
		glGenFramebuffers(1, &_msaa_fbo);
		glBindFramebuffer(GL_FRAMEBUFFER, _msaa_fbo);

		glGenRenderbuffers(1, &_msaa_rbo_color);
		glBindRenderbuffer(GL_RENDERBUFFER, _msaa_rbo_color);
		glRenderbufferStorageMultisample(GL_RENDERBUFFER, _fbo_msaa_count, GL_RGBA8, _fbo_width, _fbo_height);

		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, _msaa_rbo_color);

		glGenRenderbuffers(1, &_msaa_rbo_depth);
		glBindRenderbuffer(GL_RENDERBUFFER, _msaa_rbo_depth);
		glRenderbufferStorageMultisample(GL_RENDERBUFFER, _fbo_msaa_count, GL_DEPTH_COMPONENT, _fbo_width, _fbo_height);

		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, _msaa_rbo_depth);

		status = get_status();
	}

	glBindRenderbuffer(GL_RENDERBUFFER, 0);
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	return status;
}

void FrameBuffer::destroy() {
	if (!_fbo) {
		return;
	}

	if (_msaa_rbo_color) {
		glDeleteRenderbuffers(1, &_msaa_rbo_color);
		_msaa_rbo_color = 0;
	}

	if (_msaa_rbo_depth) {
		glDeleteRenderbuffers(1, &_msaa_rbo_depth);
		_msaa_rbo_depth = 0;
	}

	if (_msaa_fbo) {
		glDeleteFramebuffers(1, &_msaa_fbo);
		_msaa_fbo = 0;
	}

	if (_texture) {
		glDeleteTextures(1, &_texture);
		_texture = 0;
	}

	if (_rbo) {
		glDeleteRenderbuffers(1, &_rbo);
		_rbo = 0;
	}

	if (_fbo) {
		glDeleteFramebuffers(1, &_fbo);
		_fbo = 0;
	}
}

int FrameBuffer::get_status() {
	GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);

	return status;
}

uint32_t FrameBuffer::get_gl_fbo() {
	if (!_msaa_fbo) {
		return _fbo;
	}

	return _msaa_fbo;
}

uint32_t FrameBuffer::get_gl_texture() {
	return _texture;
}

void FrameBuffer::bind() {
	glBindFramebuffer(GL_FRAMEBUFFER, get_gl_fbo());
}
void FrameBuffer::unbind() {
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
void FrameBuffer::update() {
	if (_fbo_msaa_count > 0) {
		glBindFramebuffer(GL_READ_FRAMEBUFFER, _msaa_fbo);
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, _fbo);
		glBlitFramebuffer(0, 0, _fbo_width, _fbo_height, 0, 0, _fbo_width, _fbo_height, GL_COLOR_BUFFER_BIT, GL_LINEAR);
		glBlitFramebuffer(0, 0, _fbo_width, _fbo_height, 0, 0, _fbo_width, _fbo_height, GL_DEPTH_BUFFER_BIT, GL_NEAREST);
	}

	if (((_texture_flags & FRAMEBUFFER_TEXTURE_FLAG_MIP_MAPS) > 0)) {
		glBindTexture(GL_TEXTURE_2D, _texture);
		glGenerateMipmap(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}

Ref<Image> FrameBuffer::get_image_color() {
	Ref<Image> img;
	img.instance();

	Vector<uint8_t> cb = get_color_buffer();

	img->create(_fbo_width, _fbo_height, false, Image::FORMAT_RGBA8, cb);

	if (((_texture_flags & FRAMEBUFFER_TEXTURE_FLAG_MIP_MAPS) > 0)) {
		img->generate_mipmaps();
	}

	return img;
}
Ref<Image> FrameBuffer::get_image_depth() {
	Ref<Image> img;
	img.instance();

	Vector<float> db = get_depth_buffer();

	img->create(_fbo_width, _fbo_height, false, Image::FORMAT_RF);

	ERR_FAIL_COND_V(db.size() * (int)sizeof(float) != img->get_data_size(), img);

	const float *db_ptr = db.ptr();
	float *ifptr = (float *)img->dataw();
	int db_size = db.size();
	for (int i = 0; i < db_size; ++i) {
		ifptr[i] = db_ptr[i];
	}

	if (((_texture_flags & FRAMEBUFFER_TEXTURE_FLAG_MIP_MAPS) > 0)) {
		img->generate_mipmaps();
	}

	return img;
}
Vector<uint8_t> FrameBuffer::get_color_buffer() {
	Vector<uint8_t> color_buffer;
	color_buffer.resize(_fbo_width * _fbo_height * 4);

	if (_fbo_msaa_count > 0) {
		blit_color_to(_fbo);
	}

	glBindFramebuffer(GL_READ_FRAMEBUFFER, _fbo);
	glReadPixels(0, 0, _fbo_width, _fbo_height, GL_RGBA, GL_UNSIGNED_BYTE, color_buffer.ptrw());

	return color_buffer;
}
Vector<float> FrameBuffer::get_depth_buffer() {
	Vector<float> depth_buffer;
	depth_buffer.resize(_fbo_width * _fbo_height);

	if (_fbo_msaa_count > 0) {
		blit_depth_to(_fbo);
	}

	glBindFramebuffer(GL_READ_FRAMEBUFFER, _fbo);
	glReadPixels(0, 0, _fbo_width, _fbo_height, GL_DEPTH_COMPONENT, GL_FLOAT, depth_buffer.ptrw());

	return depth_buffer;
}

Vector2i FrameBuffer::get_size() const {
	return Vector2i(_fbo_width, _fbo_height);
}

void FrameBuffer::blit_color_to(const uint32_t p_destination_framebuffer, const Rect2i &p_rect) {
	ERR_FAIL_COND(!p_destination_framebuffer);

	int width = p_rect.size.width == 0 ?_fbo_width : p_rect.size.width;
	int height = p_rect.size.height == 0 ? _fbo_height : p_rect.size.height;

	uint32_t fbo = get_gl_fbo();

	glBindFramebuffer(GL_READ_FRAMEBUFFER, fbo);
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, p_destination_framebuffer);
	glBlitFramebuffer(0, 0, _fbo_width, _fbo_height, p_rect.position.x, p_rect.position.y, width, height, GL_COLOR_BUFFER_BIT, GL_LINEAR);
}

void FrameBuffer::blit_depth_to(const uint32_t p_destination_framebuffer, const Rect2i &p_rect) {
	ERR_FAIL_COND(!p_destination_framebuffer);

	int width = p_rect.size.width == 0 ?_fbo_width : p_rect.size.width;
	int height = p_rect.size.height == 0 ? _fbo_height : p_rect.size.height;

	uint32_t fbo = get_gl_fbo();

	glBindFramebuffer(GL_READ_FRAMEBUFFER, fbo);
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, p_destination_framebuffer);
	glBlitFramebuffer(0, 0, _fbo_width, _fbo_height, p_rect.position.x, p_rect.position.y, width, height, GL_DEPTH_BUFFER_BIT, GL_NEAREST);
}

void FrameBuffer::set_as_viewport() {
	RenderState::current_framebuffer = Ref<FrameBuffer>(this);
	RenderState::render_rect = Rect2i(0, 0, _fbo_width, _fbo_height);
	RenderState::apply_render_rect();
}

void FrameBuffer::reset_as_viewport() {
	RenderState::current_framebuffer.unref();
	RenderState::render_rect = Rect2i(0, 0, AppWindow::get_singleton()->get_width(), AppWindow::get_singleton()->get_height());
	RenderState::apply_render_rect();
}

float FrameBuffer::get_aspect() const {
	return _fbo_width / (float)_fbo_height;
}

FrameBuffer::FrameBuffer() {
	_texture = 0;

	_msaa_fbo = 0;
	_msaa_rbo_color = 0;
	_msaa_rbo_depth = 0;

	_fbo_width = 0;
	_fbo_height = 0;
	_fbo_msaa_count = 0;

	_rbo = 0;
	_fbo = 0;
	_texture_flags = 0;
}

FrameBuffer::~FrameBuffer() {
	destroy();
}
