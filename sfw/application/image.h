/*************************************************************************/
/*  image.h                                                              */
/*************************************************************************/
/*                       This file is part of:                           */
/*                           GODOT ENGINE                                */
/*                      https://godotengine.org                          */
/*************************************************************************/
/* Copyright (c) 2007-2022 Juan Linietsky, Ariel Manzur.                 */
/* Copyright (c) 2014-2022 Godot Engine contributors (cf. AUTHORS.md).   */
/*                                                                       */
/* Permission is hereby granted, free of charge, to any person obtaining */
/* a copy of this software and associated documentation files (the       */
/* "Software"), to deal in the Software without restriction, including   */
/* without limitation the rights to use, copy, modify, merge, publish,   */
/* distribute, sublicense, and/or sell copies of the Software, and to    */
/* permit persons to whom the Software is furnished to do so, subject to */
/* the following conditions:                                             */
/*                                                                       */
/* The above copyright notice and this permission notice shall be        */
/* included in all copies or substantial portions of the Software.       */
/*                                                                       */
/* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,       */
/* EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF    */
/* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.*/
/* IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY  */
/* CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,  */
/* TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE     */
/* SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.                */
/*************************************************************************/

#ifndef IMAGE_H
#define IMAGE_H

#include "core/math/color.h"
#include "core/math/rect2.h"
#include "core/containers/vector.h"
#include "core/resource.h"
#include "core/math/rect2i.h"
#include "core/math/vector2i.h"

class Image : public Resource {
	RCPP_OBJECT(Image, Resource);

public:
	enum {
		MAX_WIDTH = 16384, // force a limit somehow
		MAX_HEIGHT = 16384 // force a limit somehow
	};

	enum Format {

		FORMAT_L8, //luminance
		FORMAT_LA8, //luminance-alpha
		FORMAT_R8,
		FORMAT_RG8,
		FORMAT_RGB8,
		FORMAT_RGBA8,
		FORMAT_RGBA4444,
		FORMAT_RGBA5551,
		FORMAT_RF, //float
		FORMAT_RGF,
		FORMAT_RGBF,
		FORMAT_RGBAF,
		FORMAT_RH, //half float
		FORMAT_RGH,
		FORMAT_RGBH,
		FORMAT_RGBAH,
		FORMAT_RGBE9995,
		FORMAT_DXT1, //s3tc bc1
		FORMAT_DXT3, //bc2
		FORMAT_DXT5, //bc3
		FORMAT_RGTC_R,
		FORMAT_RGTC_RG,
		FORMAT_BPTC_RGBA, //btpc bc7
		FORMAT_BPTC_RGBF, //float bc6h
		FORMAT_BPTC_RGBFU, //unsigned float bc6hu
		FORMAT_PVRTC2, //pvrtc
		FORMAT_PVRTC2A,
		FORMAT_PVRTC4,
		FORMAT_PVRTC4A,
		FORMAT_ETC, //etc1
		FORMAT_ETC2_R11, //etc2
		FORMAT_ETC2_R11S, //signed, NOT srgb.
		FORMAT_ETC2_RG11,
		FORMAT_ETC2_RG11S,
		FORMAT_ETC2_RGB8,
		FORMAT_ETC2_RGBA8,
		FORMAT_ETC2_RGB8A1,
		FORMAT_MAX
	};

	static const char *format_names[FORMAT_MAX];
	enum Interpolation {

		INTERPOLATE_NEAREST,
		INTERPOLATE_BILINEAR,
		INTERPOLATE_CUBIC,
		INTERPOLATE_TRILINEAR,
		INTERPOLATE_LANCZOS,
		/* INTERPOLATE_TRICUBIC, */
		/* INTERPOLATE GAUSS */
	};

	enum CompressSource {
		COMPRESS_SOURCE_GENERIC,
		COMPRESS_SOURCE_SRGB,
		COMPRESS_SOURCE_NORMAL,
		COMPRESS_SOURCE_LAYERED,
		COMPRESS_SOURCE_MAX,
	};

	bool write_lock;

private:
	void _create_empty(int p_width, int p_height, bool p_use_mipmaps, Format p_format) {
		create(p_width, p_height, p_use_mipmaps, p_format);
	}

	void _create_from_data(int p_width, int p_height, bool p_use_mipmaps, Format p_format, const Vector<uint8_t> &p_data) {
		create(p_width, p_height, p_use_mipmaps, p_format, p_data);
	}

	Format format;
	Vector<uint8_t> data;
	int width, height;
	bool mipmaps;

	void _copy_internals_from(const Image &p_image) {
		format = p_image.format;
		width = p_image.width;
		height = p_image.height;
		mipmaps = p_image.mipmaps;
		data = p_image.data;
	}

	_FORCE_INLINE_ void _get_mipmap_offset_and_size(int p_mipmap, int &r_offset, int &r_width, int &r_height) const; //get where the mipmap begins in data

	static int _get_dst_image_size(int p_width, int p_height, Format p_format, int &r_mipmaps, int p_mipmaps = -1);
	bool _can_modify(Format p_format) const;

	_FORCE_INLINE_ void _put_pixelb(int p_x, int p_y, uint32_t p_pixel_size, uint8_t *p_data, const uint8_t *p_pixel);
	_FORCE_INLINE_ void _get_pixelb(int p_x, int p_y, uint32_t p_pixel_size, const uint8_t *p_data, uint8_t *p_pixel);

	_FORCE_INLINE_ void _repeat_pixel_over_subsequent_memory(uint8_t *p_pixel, int p_pixel_size, int p_count);

	static void average_4_uint8(uint8_t &p_out, const uint8_t &p_a, const uint8_t &p_b, const uint8_t &p_c, const uint8_t &p_d);
	static void average_4_float(float &p_out, const float &p_a, const float &p_b, const float &p_c, const float &p_d);
	static void average_4_half(uint16_t &p_out, const uint16_t &p_a, const uint16_t &p_b, const uint16_t &p_c, const uint16_t &p_d);
	static void average_4_rgbe9995(uint32_t &p_out, const uint32_t &p_a, const uint32_t &p_b, const uint32_t &p_c, const uint32_t &p_d);
	static void renormalize_uint8(uint8_t *p_rgb);
	static void renormalize_float(float *p_rgb);
	static void renormalize_half(uint16_t *p_rgb);
	static void renormalize_rgbe9995(uint32_t *p_rgb);

public:
	int get_width() const; ///< Get image width
	int get_height() const; ///< Get image height
	Vector2 get_size() const;
	bool has_mipmaps() const;
	int get_mipmap_count() const;

	/**
	 * Convert the image to another format, conversion only to raw byte format
	 */
	void convert(Format p_new_format);

	/**
	 * Get the current image format.
	 */
	Format get_format() const;

	int get_mipmap_offset(int p_mipmap) const; //get where the mipmap begins in data
	void get_mipmap_offset_and_size(int p_mipmap, int &r_ofs, int &r_size) const; //get where the mipmap begins in data
	void get_mipmap_offset_size_and_dimensions(int p_mipmap, int &r_ofs, int &r_size, int &w, int &h) const; //get where the mipmap begins in data

	/**
	 * Resize the image, using the preferred interpolation method.
	 */
	void resize_to_po2(bool p_square = false, Interpolation p_interpolation = INTERPOLATE_BILINEAR);
	void resize(int p_width, int p_height, Interpolation p_interpolation = INTERPOLATE_BILINEAR);
	void shrink_x2();
	bool is_size_po2() const;
	/**
	 * Crop the image to a specific size, if larger, then the image is filled by black
	 */
	void crop_from_point(int p_x, int p_y, int p_width, int p_height);
	void crop(int p_width, int p_height);

	void flip_x();
	void flip_y();

	/**
	 * Generate a mipmap to an image (creates an image 1/4 the size, with averaging of 4->1)
	 */
	int generate_mipmaps(bool p_renormalize = false);

	void clear_mipmaps();
	void normalize(); //for normal maps

	/**
	 * Create a new image of a given size and format. Current image will be lost
	 */
	void create(int p_width, int p_height, bool p_use_mipmaps, Format p_format);
	void create(int p_width, int p_height, bool p_use_mipmaps, Format p_format, const Vector<uint8_t> &p_data);

	void create(const char **p_xpm);
	/**
	 * returns true when the image is empty (0,0) in size
	 */
	bool empty() const;

	Vector<uint8_t> get_data() const;
	const uint8_t* datar() const;
	uint8_t* dataw();
	int get_data_size() const;

	Image();
	Image(int p_width, int p_height, bool p_use_mipmaps, Format p_format);
	Image(int p_width, int p_height, bool p_mipmaps, Format p_format, const Vector<uint8_t> &p_data);

	enum AlphaMode {
		ALPHA_NONE,
		ALPHA_BIT,
		ALPHA_BLEND
	};

	AlphaMode detect_alpha() const;
	bool is_invisible() const;

	static int get_format_pixel_size(Format p_format);
	static int get_format_pixel_rshift(Format p_format);
	static int get_format_block_size(Format p_format);
	static void get_format_min_pixel_size(Format p_format, int &r_w, int &r_h);

	static int get_image_data_size(int p_width, int p_height, Format p_format, bool p_mipmaps = false);
	static int get_image_required_mipmaps(int p_width, int p_height, Format p_format);
	static int get_image_mipmap_offset(int p_width, int p_height, Format p_format, int p_mipmap);

	enum CompressMode {
		COMPRESS_S3TC,
		COMPRESS_PVRTC2,
		COMPRESS_PVRTC4,
		COMPRESS_ETC,
		COMPRESS_ETC2,
		COMPRESS_BPTC,
		COMPRESS_MAX,
	};

	bool is_compressed() const;

	void fix_alpha_edges();
	void premultiply_alpha();
	void srgb_to_linear();
	void normalmap_to_xy();
	Ref<Image> rgbe_to_srgb();
	void bumpmap_to_normalmap(float bump_scale = 1.0);

	void blit_rect(const Ref<Image> &p_src, const Rect2 &p_src_rect, const Vector2 &p_dest);
	void blit_rect_mask(const Ref<Image> &p_src, const Ref<Image> &p_mask, const Rect2 &p_src_rect, const Vector2 &p_dest);
	void blend_rect(const Ref<Image> &p_src, const Rect2 &p_src_rect, const Vector2 &p_dest);
	void blend_rect_mask(const Ref<Image> &p_src, const Ref<Image> &p_mask, const Rect2 &p_src_rect, const Vector2 &p_dest);
	void fill(const Color &p_color);
	void fill_rect(const Rect2 &p_rect, const Color &p_color);

	Rect2 get_used_rect() const;
	Ref<Image> get_rect(const Rect2 &p_area) const;

	static void set_compress_bc_func(void (*p_compress_func)(Image *, float, CompressSource));
	static void set_compress_bptc_func(void (*p_compress_func)(Image *, float, CompressSource));
	static String get_format_name(Format p_format);

	Image(const char **p_xpm);

	virtual Ref<Resource> duplicate(bool p_subresources = false) const;

	void lock();
	void unlock();

	//this is used for compression
	enum DetectChannels {
		DETECTED_L,
		DETECTED_LA,
		DETECTED_R,
		DETECTED_RG,
		DETECTED_RGB,
		DETECTED_RGBA,
	};

	DetectChannels get_detected_channels();
	void optimize_channels();

	Color get_pixelv(const Vector2 &p_src) const;
	Color get_pixel(int p_x, int p_y) const;
	void set_pixelv(const Vector2 &p_dst, const Color &p_color);
	void set_pixel(int p_x, int p_y, const Color &p_color);

	void copy_internals_from(const Ref<Image> &p_image) {
		ERR_FAIL_COND(p_image.is_null());

		format = p_image->format;
		width = p_image->width;
		height = p_image->height;
		mipmaps = p_image->mipmaps;
		data = p_image->data;
	}

	~Image();
};

#endif
