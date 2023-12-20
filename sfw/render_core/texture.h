#ifndef TEXTURE_H
#define TEXTURE_H

#include "3rd_glad.h"

class Texture {
public:
	enum TextureFilter {
		TEXTURE_FILTER_NEAREST = 0,
		TEXTURE_FILTER_LINEAR,
	};

	void load_image(const char *file_name, const int format = GL_RGBA, const int internal_components = GL_RGBA);
	void apply_filter();

	TextureFilter filter;
	GLuint texture;

	// from fwk, temporary
	union {
		int x, w;
	};
	union {
		int y, h;
	};
	union {
		int n, comps;
	};
	union {
		void *pixels;
		uint8_t *pixels8;
		uint16_t *pixels16;
		uint32_t *pixels32;
		float *pixelsf;
	};

	// From FWK
	void image_data_load(const char *file_name, int flags);
	void texture_update(int flags);

	Texture();
	virtual ~Texture();
};

#endif // TEXTURE_H
