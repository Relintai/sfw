#ifndef TEXTURE_H
#define TEXTURE_H

#include "3rd_glad.h"
#include "image.h"

class Texture {
public:
	enum TextureFilter {
		TEXTURE_FILTER_NEAREST = 0,
		TEXTURE_FILTER_LINEAR,
	};

	TextureFilter filter;
	GLuint texture;

	void apply_filter();
	void texture_update(int flags);

	void set_image(const Ref<Image> &img);

	Texture();
	virtual ~Texture();

protected:
	int _image_width;
	int _image_height;
	Ref<Image> _image;
	Vector<uint8_t> _image_data;
	Image::Format _image_format;
	bool _image_mip_maps;
};

#endif // TEXTURE_H
