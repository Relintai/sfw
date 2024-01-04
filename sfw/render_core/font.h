#ifndef FONT_RENDERER_H
#define FONT_RENDERER_H

// -----------------------------------------------------------------------------
// font framework originally from FWK
// - rlyeh, public domain

#include "object/resource.h"

#include "core/ustring.h"
#include "font_material.h"

// TODO figure out how to forward declare stbtt_packedchar
#include "3rd_stb_truetype.h"

class Image;
class Texture;

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

	typedef struct font_metrics_t {
		float ascent; // max distance above baseline for all glyphs
		float descent; // max distance below baseline for all glyphs
		float linegap; // distance betwen ascent of next line and descent of current line
		float linedist; // distance between the baseline of two lines (ascent - descent + linegap)
	} font_metrics_t;

	void load_default(const float size, const uint32_t flags = 0);

	float get_scale() const;
	void set_scale(const float p_scale);

	// configures
	void font_face(const char *filename_ttf, float font_size, uint32_t flags);
	void font_face_from_mem(const void *ttf_buffer, uint32_t ttf_len, float font_size, uint32_t flags);

	// commands
	Vector2 font_xy();
	void font_goto(float x, float y);
	Vector2 font_print(const String &text);
	Vector2 font_rect(const String &str);
	font_metrics_t font_metrics(const String &text);

	int get_atlas_width();
	int get_atlas_height();

	Ref<Image> get_image();
	Ref<Texture> get_texture();

	Font();

protected:
	// character info
	// filled up by stb_truetype.h
	stbtt_packedchar *_cdata;
	unsigned _num_glyphs;
	unsigned *_cp2iter;
	unsigned *_iter2cp;
	unsigned _begin; // first glyph. used in cp2iter table to clamp into a lesser range

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
		float x;
		float y;
		float w;
		float h;

		float xoff;
		float yoff;
		float woff;
		float hoff;
	};

	Vector<TextureOffset> _texture_offsets;

	static void font_draw_cmd(const float *glyph_data, int glyph_idx, float factor, Vector2 offset);
	Vector2 font_draw_ex(const String &text, Vector2 offset, const char *col, void (*draw_cmd)(const float *, int, float, Vector2));

	Vector2 gotoxy;
};

#endif
