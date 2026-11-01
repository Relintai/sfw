//--STRIP
#ifndef TEXTURE_H
#define TEXTURE_H
//--STRIP

//--STRIP
#include "core/vector2i.h"

#include "object/resource.h"
#include "render_core/image.h"
//--STRIP

class FrameBuffer;

class Texture : public Resource {
	SFW_OBJECT(Texture, Resource);

public:
	enum TextureFlags {
		TEXTURE_FLAG_FILTER = 1 << 0,
		TEXTURE_FLAG_REPEAT = 1 << 1,
		TEXTURE_FLAG_MIRRORED_REPEAT = 1 << 2,
		TEXTURE_FLAG_MIP_MAPS = 1 << 3,
	};

	_FORCE_INLINE_ uint32_t get_gl_texture() {
		return _texture;
	}

	void create_from_image(const Ref<Image> &img);

	Ref<Image> get_data();

	Vector2i get_size() const;

	void upload();

	Texture();
	virtual ~Texture();

protected:
	void _get_gl_format(Image::Format p_format, uint32_t &r_gl_format, uint32_t &r_gl_internal_format, uint32_t &r_gl_type, bool &r_supported) const;

	Ref<Image> _image;

	int _texture_width;
	int _texture_height;
	Image::Format _texture_format;

	int _flags;
	int _texture_index;
	int _data_size;
	int _mipmaps;

	uint32_t _texture;
};

class RenderTexture : public Texture {
public:
	enum RenderTextureType {
		RENDER_TEXTURE_TYPE_COLOR = 0,
		RENDER_TEXTURE_TYPE_DEPTH,
	};

	bool get_v_flip() const;
	void set_v_flip(const bool p_v_flip);

	RenderTextureType get_type() const;
	void set_type(const RenderTextureType p_type);

	Ref<FrameBuffer> get_frame_buffer() const;
	void set_frame_buffer(const Ref<FrameBuffer> &p_frame_buffer);

	void update();

	RenderTexture();
	virtual ~RenderTexture();

protected:
	bool _v_flip;
	Ref<FrameBuffer> _frame_buffer;
	RenderTextureType _type;
};

//--STRIP
#endif // TEXTURE_H
//--STRIP
