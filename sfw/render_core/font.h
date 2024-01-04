#ifndef FONT_RENDERER_H
#define FONT_RENDERER_H

// -----------------------------------------------------------------------------
// font framework originally from FWK
// - rlyeh, public domain

#include "core/color.h"
#include "core/ustring.h"

#include "object/resource.h"

#include "core/ustring.h"
#include "font_material.h"

class Image;
class Texture;
class Mesh;

class Font : public Resource {
	SFW_OBJECT(Font, Resource);

public:
	// font flags
	enum FONT_FLAGS {
		// font atlas size
		FONT_512 = 0x0,
		FONT_1024 = 0x1,
		FONT_2048 = 0x2,
		FONT_4096 = 0x4,

		// font oversampling
		FONT_NO_OVERSAMPLE = 0x0,
		FONT_OVERSAMPLE_X = 0x08,
		FONT_OVERSAMPLE_Y = 0x10,

		// unicode ranges
		FONT_ASCII = 0x800, // Compatible charset
		FONT_AR = 0x001000, // Arabic and Arabic-Indic digits
		FONT_ZH = 0x002000, // Chinese Simplified (@todo: add ZH_FULL)
		FONT_EL = 0x004000, // Greek, Coptic, modern Georgian, Svan, Mingrelian, Ancient Greek
		FONT_EM = 0x008000, // Emoji
		FONT_EU = 0x010000, // Eastern/western Europe, IPA, Latin ext A/B
		FONT_HE = 0x020000, // Hebrew, Yiddish, Ladino, and other diaspora languages
		FONT_JP = 0x040000, // Hiragana, Katakana, Punctuations, Half-width chars
		FONT_KR = 0x080000, // Korean, Hangul
		FONT_RU = 0x100000, // Cyrillic + ext A/B
		FONT_TH = 0x200000, // Thai
		FONT_VI = 0x400000, // Vietnamese
		FONT_CJK = FONT_ZH | FONT_JP | FONT_KR,

		// FONT_DEFAULTS = FONT_512 | FONT_NO_OVERSAMPLE | FONT_ASCII,
	};

	struct FontMetrics {
		float ascent; // max distance above baseline for all glyphs
		float descent; // max distance below baseline for all glyphs
		float linegap; // distance betwen ascent of next line and descent of current line
		float linedist; // distance between the baseline of two lines (ascent - descent + linegap)
	};

	void load_default(const float size, const uint32_t flags = 0);

	float get_scale() const;
	void set_scale(const float p_scale);

	// configures
	void font_face(const char *filename_ttf, float font_size, uint32_t flags);
	void font_face_from_mem(const void *ttf_buffer, uint32_t ttf_len, float font_size, uint32_t flags);

	// commands
	Vector2 generate_mesh(const String &p_text, Ref<Mesh> &p_into, const Color &p_color = Color(1, 1, 1, 1));
	Vector2 get_string_size(const String &p_text);
	FontMetrics font_metrics();

	int get_atlas_width();
	int get_atlas_height();

	Ref<Image> get_image();
	Ref<Texture> get_texture();

	void unload();

	Font();
	~Font();

protected:
	// character info
	// filled up by stb_truetype.h
	uint32_t _num_glyphs;
	uint32_t *_cp2iter;
	uint32_t *_iter2cp;
	uint32_t _begin; // first glyph. used in cp2iter table to clamp into a lesser range

	// font info and data
	bool _initialized;

	int _height; // bitmap height
	int _width; // bitmap width
	float _font_size; // font size in pixels (matches scale[0+1] size below)
	float _factor; // font factor (font_size / (ascent - descent))
	float _scale;

	// displacement info
	float _ascent; // max distance above baseline for all glyphs
	float _descent; // max distance below baseline for all glyphs
	float _linegap; // distance betwen ascent of next line and descent of current line
	float _linedist; // distance between the baseline of two lines (ascent - descent + linegap)

	// opengl stuff
	Ref<Image> _image;
	Ref<Texture> _texture;

	struct TextureOffset {
		float x0;
		float y0;
		float x1;
		float y1;

		float x0_orig;
		float y0_orig;
		float x1_orig;
		float y1_orig;

		float xoff;
		float xoff2;
		float xadvance;
		float yoff;
		float yoff2;
	};

	Vector<TextureOffset> _texture_offsets;
};

#endif
