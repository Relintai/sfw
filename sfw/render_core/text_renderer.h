#ifndef FONT_RENDERER_H
#define FONT_RENDERER_H

// -----------------------------------------------------------------------------
// font framework originally from FWK
// - rlyeh, public domain

#include "object/object.h"

#include "core/ustring.h"

#include "text_material.h"

// TODO figure out how to forward declare stbtt_packedchar
#include "3rd_stb_truetype.h"

// font size tags
#define FONT_H1 "\1" // largest
#define FONT_H2 "\2"
#define FONT_H3 "\3"
#define FONT_H4 "\4"
#define FONT_H5 "\5"
#define FONT_H6 "\6" // smallest

// font color tags
#define FONT_COLOR1 "\x1a"
#define FONT_COLOR2 "\x1b"
#define FONT_COLOR3 "\x1c"
#define FONT_COLOR4 "\x1d"
#define FONT_COLOR5 "\x1e"
#define FONT_COLOR6 "\x1f"

// font face tags
#define FONT_FACE1 "\x10"
#define FONT_FACE2 "\x11"
#define FONT_FACE3 "\x12"
#define FONT_FACE4 "\x13"
#define FONT_FACE5 "\x14"
#define FONT_FACE6 "\x15"
#define FONT_FACE7 "\x16"
#define FONT_FACE8 "\x17" // editor may override this one
#define FONT_FACE9 "\x18" // editor may override this one
#define FONT_FACE10 "\x19" // editor may override this one

// font align tags
#define FONT_LEFT "\\<"
#define FONT_CENTER "\\|"
#define FONT_RIGHT "\\>"
#define FONT_TOP "\\^"
#define FONT_MIDDLE "\\-"
#define FONT_BASELINE "\\_"
#define FONT_BOTTOM "\\v"

class TextRenderer : public Object {
	SFW_OBJECT(TextRenderer, Object);

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

	void font_init();

	// configures
	void font_face(const char *face_tag, const char *filename_ttf, float font_size, unsigned flags);
	void font_face_from_mem(const char *tag, const void *ttf_buffer, unsigned ttf_len, float font_size, unsigned flags);
	void font_scales(const char *face_tag, float h1, float h2, float h3, float h4, float h5, float h6);
	void font_color(const char *color_tag, uint32_t color);

	// commands
	Vector2 font_xy();
	void font_goto(float x, float y);
	Vector2 font_print(const String &text);
	Vector2 font_rect(const String &str);
	font_metrics_t font_metrics(const String &text);

	static TextRenderer *get_singleton();

	TextRenderer();

protected:
	bool _fonts_initialized;

	enum { FONT_MAX_COLORS = 256 };
	enum { FONT_MAX_STRING_LEN = 40000 }; // more glyphs than any reasonable person would show on the screen at once. you can only fit 20736 10x10 rects in a 1920x1080 window

	static uint32_t font_palette[FONT_MAX_COLORS];

	typedef struct font_t {
		bool initialized; 

		//char filename[256];

		// character info
		// filled up by stb_truetype.h
		stbtt_packedchar *cdata;
		unsigned num_glyphs;
		unsigned *cp2iter;
		unsigned *iter2cp;
		unsigned begin; // first glyph. used in cp2iter table to clamp into a lesser range

		// font info and data
		int height; // bitmap height
		int width; // bitmap width
		float font_size; // font size in pixels (matches scale[0+1] size below)
		float factor; // font factor (font_size / (ascent - descent))
		float scale[7]; // user defined font scale (match H1..H6 tags)

		// displacement info
		float ascent; // max distance above baseline for all glyphs
		float descent; // max distance below baseline for all glyphs
		float linegap; // distance betwen ascent of next line and descent of current line
		float linedist; // distance between the baseline of two lines (ascent - descent + linegap)

		// opengl stuff
		GLuint vao;
		Ref<TextMaterial> program;

		// font bitmap texture
		// generated using stb_truetype.h
		GLuint texture_fontdata;

		// metadata texture.
		// first row contains information on which parts of the bitmap correspond to a glyph.
		// the second row contain information about the relative displacement of the glyph relative to the cursor position
		GLuint texture_offsets;

		// color texture
		// used to color each glyph individually, e.g. for syntax highlighting
		GLuint texture_colors;

		// vbos
		GLuint vbo_quad; // Vector2: simply just a regular [0,1]x[0,1] quad
		GLuint vbo_instances; // vec4: (char_pos_x, char_pos_y, char_index, color_index)
	} font_t;

	enum { FONTS_MAX = 10 };

	font_t fonts[FONTS_MAX];

	static void font_draw_cmd(font_t *f, const float *glyph_data, int glyph_idx, float factor, Vector2 offset);
	Vector2 font_draw_ex(const String &text, Vector2 offset, const char *col, void (*draw_cmd)(font_t *, const float *, int, float, Vector2));

	Vector2 gotoxy;

	static TextRenderer *_singleton;
};

#endif
