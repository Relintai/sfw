//--STRIP
#ifndef FRAME_BUFFER_H
#define FRAME_BUFFER_H
//--STRIP

//--STRIP
#include "core/vector2i.h"

#include "object/resource.h"
#include "render_core/3rd_glad.h"
#include "render_core/image.h"
//--STRIP

class FrameBuffer : public Resource {
	SFW_OBJECT(FrameBuffer, Resource);

public:
	enum FrameBufferFlags {
		FRAMEBUFFER_TEXTURE_FLAG_FILTER = 1 << 0,
		FRAMEBUFFER_TEXTURE_FLAG_REPEAT = 1 << 1,
		FRAMEBUFFER_TEXTURE_FLAG_MIRRORED_REPEAT = 1 << 2,
		FRAMEBUFFER_TEXTURE_FLAG_MIP_MAPS = 1 << 3,
	};

	int get_texture_flags() const;
	void set_texture_flags(const int p_flags);

	int create(const int p_width, const int p_height, const int p_msaa_count = 0);
	void destroy();

	int get_status();

	uint32_t get_gl_fbo();
	uint32_t get_gl_texture();

	void bind();
	void unbind();
	void update();

	Ref<Image> get_image_color();
	Ref<Image> get_image_depth();

	Vector<uint8_t> get_color_buffer();
	Vector<float> get_depth_buffer();

	Vector2i get_size() const;

	void blit_color_to(const uint32_t p_destination_framebuffer, const Rect2i &p_rect = Rect2i());
	void blit_depth_to(const uint32_t p_destination_framebuffer, const Rect2i &p_rect = Rect2i());

	void set_as_viewport();
	void reset_as_viewport();

	float get_aspect() const;

	FrameBuffer();
	virtual ~FrameBuffer();

protected:
	uint32_t _texture;

	uint32_t _msaa_fbo;
	uint32_t _msaa_rbo_color;
	uint32_t _msaa_rbo_depth;

	int _fbo_width;
	int _fbo_height;
	int _fbo_msaa_count;

	uint32_t _rbo;
	uint32_t _fbo;

	int _texture_flags;
};

//--STRIP
#endif // TEXTURE_H
//--STRIP
