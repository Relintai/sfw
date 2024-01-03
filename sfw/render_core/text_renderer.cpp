// font framework. original code by Vassvik (UNLICENSED)
// - rlyeh, public domain.
//
// [x] embedded default font (bm mini).
// [x] oversampling, texture dimensions.
// [x] utf8, unicode ranges.
// [x] markup opcodes.
// [x] faces (italic, bold, regular, cjk), colors and sizes.
// [x] unicode ranges from dear-imgui (@ocornut allowed to mit-0 relicense the data tables).
// [*] alignment. kinda hacky. revisit some day.
// [ ] underlining, soft/hard shadows, outlines.
// [ ] clip/wrap/overflow regions.
// [ ] text-shaping, text-layout.
// [ ] text-wrapping.
// [ ] optimizations.
//
// ## language families that could be merged on a single texture alias
// - EU+EL+RU
// - AR+HE+RU
// - TH+VI+TW
// - ZH
// - JP
// - KR

// -----------------------------------------------------------------------------

// bm-mini.zip (public domain font)
// http://bitmapmania.m78.com
// cooz@m78.com

#include "font_data_bm_mini.inc.h"

// -----------------------------------------------------------------------------

static const char mv_vs_source[] = "//" FILELINE /*#version 330 core\n\*/ "\
\n\
in vec2 vertexPosition;\n\
in vec4 instanceGlyph;\n\
\n\
uniform sampler2D sampler_font;\n\
uniform sampler2D sampler_meta;\n\
\n\
uniform float offset_firstline; // ascent - descent - linegap/2\n\
uniform float scale_factor;     // scaling factor proportional to font size\n\
uniform vec2 string_offset;     // offset of upper-left corner\n\
\n\
uniform vec2 res_meta;   // 96x2 \n\
uniform vec2 res_bitmap; // 512x256\n\
uniform vec2 resolution; // screen resolution\n\
\n\
out vec2 uv;\n\
out float color_index; // for syntax highlighting\n\
\n\
void main() { \
    // (xoff, yoff, xoff2, yoff2), from second row of texture\n\
    vec4 q2 = texture(sampler_meta, vec2((instanceGlyph.z + 0.5)/res_meta.x, 0.75))*vec4(res_bitmap, res_bitmap);\n\
\n\
    vec2 p = vertexPosition*(q2.zw - q2.xy) + q2.xy; // offset and scale it properly relative to baseline\n\
    p *= vec2(1.0, -1.0);                            // flip y, since texture is upside-down\n\
    p.y -= offset_firstline;                         // make sure the upper-left corner of the string is in the upper-left corner of the screen\n\
    p *= scale_factor;                               // scale relative to font size\n\
    p += instanceGlyph.xy + string_offset;           // move glyph into the right position\n\
    p *= 2.0/resolution;                             // to NDC\n\
    p += vec2(-1.0, 1.0);                            // move to upper-left corner instead of center\n\
\n\
    gl_Position = vec4(p, 0.0, 1.0);\n\
\n\
    // (x0, y0, x1-x0, y1-y0), from first row of texture\n\
    vec4 q = texture(sampler_meta, vec2((instanceGlyph.z + 0.5)/res_meta.x, 0.25));\n\
\n\
    // send the correct uv's in the font atlas to the fragment shader\n\
    uv = q.xy + vertexPosition*q.zw;\n\
    color_index = instanceGlyph.w;\n\
}\n";

static const char mv_fs_source[] = "//" FILELINE /*#version 330 core\n\*/ "\
\n\
in vec2 uv;\n\
in float color_index;\n\
\n\
uniform sampler2D sampler_font;\n\
uniform sampler1D sampler_colors;\n\
uniform float num_colors;\n\
\n\
out vec4 outColor;\n\
\n\
void main() {\
    vec4 col = texture(sampler_colors, (color_index+0.5)/num_colors);\n\
    float s = texture(sampler_font, uv).r;\n\
    outColor = vec4(col.rgb, s*col.a);\n\
}\n";

enum { FONT_MAX_COLORS = 256 };
enum { FONT_MAX_STRING_LEN = 40000 }; // more glyphs than any reasonable person would show on the screen at once. you can only fit 20736 10x10 rects in a 1920x1080 window

static unsigned font_palette[FONT_MAX_COLORS] = {
	RGB4(248, 248, 242, 255), // foreground color
	RGB4(249, 38, 114, 255), // operator
	RGB4(174, 129, 255, 255), // numeric
	RGB4(102, 217, 239, 255), // function
	RGB4(249, 38, 114, 255), // keyword
	RGB4(117, 113, 94, 255), // comment
	RGB4(102, 217, 239, 255), // type
	RGB4(73, 72, 62, 255), // background color
	RGB4(39, 40, 34, 255), // clear color
};

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
	GLuint program;

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
	GLuint vbo_quad; // vec2: simply just a regular [0,1]x[0,1] quad
	GLuint vbo_instances; // vec4: (char_pos_x, char_pos_y, char_index, color_index)
} font_t;

enum { FONTS_MAX = 10 };

static font_t fonts[FONTS_MAX] = { 0 };

static void font_init() {
	do_once {
		font_face_from_mem(FONT_FACE1, bm_mini_ttf, countof(bm_mini_ttf), 42.5f, 0);
		font_face_from_mem(FONT_FACE2, bm_mini_ttf, countof(bm_mini_ttf), 42.5f, 0);
		font_face_from_mem(FONT_FACE3, bm_mini_ttf, countof(bm_mini_ttf), 42.5f, 0);
		font_face_from_mem(FONT_FACE4, bm_mini_ttf, countof(bm_mini_ttf), 42.5f, 0);
		font_face_from_mem(FONT_FACE5, bm_mini_ttf, countof(bm_mini_ttf), 42.5f, 0);
		font_face_from_mem(FONT_FACE6, bm_mini_ttf, countof(bm_mini_ttf), 42.5f, 0);
		font_face_from_mem(FONT_FACE7, bm_mini_ttf, countof(bm_mini_ttf), 42.5f, 0);
		font_face_from_mem(FONT_FACE8, bm_mini_ttf, countof(bm_mini_ttf), 42.5f, 0);
		font_face_from_mem(FONT_FACE9, bm_mini_ttf, countof(bm_mini_ttf), 42.5f, 0);
		font_face_from_mem(FONT_FACE10, bm_mini_ttf, countof(bm_mini_ttf), 42.5f, 0);
	}
}

// Remap color within all existing color textures
void font_color(const char *tag, uint32_t color) {
	font_init();

	unsigned index = *tag - FONT_COLOR1[0];
	if (index < FONT_MAX_COLORS) {
		font_palette[index] = color;

		for (int i = 0; i < FONTS_MAX; ++i) {
			font_t *f = &fonts[i];
			if (f->initialized) {
				glActiveTexture(GL_TEXTURE2);
				glBindTexture(GL_TEXTURE_1D, f->texture_colors);
				glTexSubImage1D(GL_TEXTURE_1D, 0, 0, FONT_MAX_COLORS, GL_RGBA, GL_UNSIGNED_BYTE, font_palette);
			}
		}
	}
}

void ui_font() {
	for (int i = 0; i < countof(fonts); ++i) {
		if (ui_collapse(va("Font %d", i), va("%p%d", &fonts[i], i))) {
			font_t *f = &fonts[i];
			ui_float("Ascent", &f->ascent);
			ui_float("Descent", &f->descent);
			ui_float("Line Gap", &f->linegap);
			f->linedist = (f->ascent - f->descent + f->linegap);
			ui_collapse_end();
		}
	}
}

void font_scales(const char *tag, float h1, float h2, float h3, float h4, float h5, float h6) {
	font_init();

	unsigned index = *tag - FONT_FACE1[0];
	if (index > FONTS_MAX)
		return;

	font_t *f = &fonts[index];
	if (!f->initialized)
		return;

	f->scale[0] = h1 / f->font_size;
	f->scale[1] = h1 / f->font_size;
	f->scale[2] = h2 / f->font_size;
	f->scale[3] = h3 / f->font_size;
	f->scale[4] = h4 / f->font_size;
	f->scale[5] = h5 / f->font_size;
	f->scale[6] = h6 / f->font_size;
}

// 1. Compile the shaders.
// 1. Call stb_truetype.h routines to read and parse a .ttf file.
// 1. Create a bitmap that is uploaded to the gpu using opengl.
// 1. Calculate and save a bunch of useful variables and put them in the global font variable.
void font_face_from_mem(const char *tag, const void *ttf_data, unsigned ttf_len, float font_size, unsigned flags) {
	unsigned index = *tag - FONT_FACE1[0];
	if (index > FONTS_MAX)
		return;
	if (font_size <= 0 || font_size > 72)
		return;
	if (!ttf_data || !ttf_len)
		return;

	if (!(flags & FONT_EM))
		flags |= FONT_ASCII; // ensure this minimal range [0020-00FF] is almost always in

	font_t *f = &fonts[index];
	f->initialized = 1;

	// load .ttf into a bitmap using stb_truetype.h
	int dim = flags & FONT_4096 ? 4096 : flags & FONT_2048 ? 2048
			: flags & FONT_1024							   ? 1024
														   : 512;
	f->width = dim;
	f->height = dim;

	// change size [h1(largest) to h3(regular) to h6(smallest)]
	f->font_size = font_size;
	f->scale[0] = 1.0000f; // H1
	f->scale[1] = 1.0000f; // H1
	f->scale[2] = 0.7500f; // H2
	f->scale[3] = 0.6600f; // H3
	f->scale[4] = 0.5000f; // H4
	f->scale[5] = 0.3750f; // H5
	f->scale[6] = 0.2500f; // H6

	const char *vs_filename = 0, *fs_filename = 0;
	const char *vs = vs_filename ? vfs_read(vs_filename) : mv_vs_source;
	const char *fs = fs_filename ? vfs_read(fs_filename) : mv_fs_source;
	f->program = shader(vs, fs, "vertexPosition,instanceGlyph", "outColor", NULL);

// figure out what ranges we're about to bake
#define MERGE_TABLE(table)                                     \
	do {                                                       \
		for (unsigned i = 0; table[i]; i += 2) {               \
			uint64_t begin = table[i + 0], end = table[i + 1]; \
			for (unsigned j = begin; j <= end; ++j) {          \
				array_push(sorted, j);                         \
			}                                                  \
		}                                                      \
	} while (0)
#define MERGE_PACKED_TABLE(codepoint_begin, table)                                     \
	do {                                                                               \
		for (int i = 0, begin = codepoint_begin, end = countof(table); i < end; i++) { \
			array_push(sorted, (unsigned)(begin + table[i]));                          \
			begin += table[i];                                                         \
		}                                                                              \
	} while (0)

	array(uint64_t) sorted = 0;
	if (flags & FONT_ASCII) {
		MERGE_TABLE(table_common);
	}
	if (flags & FONT_EM) {
		MERGE_TABLE(table_emoji);
	}
	if (flags & FONT_EU) {
		MERGE_TABLE(table_eastern_europe);
	}
	if (flags & FONT_RU) {
		MERGE_TABLE(table_western_europe);
	}
	if (flags & FONT_EL) {
		MERGE_TABLE(table_western_europe);
	}
	if (flags & FONT_AR) {
		MERGE_TABLE(table_middle_east);
	}
	if (flags & FONT_HE) {
		MERGE_TABLE(table_middle_east);
	}
	if (flags & FONT_TH) {
		MERGE_TABLE(table_thai);
	}
	if (flags & FONT_VI) {
		MERGE_TABLE(table_vietnamese);
	}
	if (flags & FONT_KR) {
		MERGE_TABLE(table_korean);
	}
	if (flags & FONT_JP) {
		MERGE_TABLE(table_chinese_japanese_common);
		MERGE_PACKED_TABLE(0x4E00, packed_table_japanese);
	}
	if (flags & FONT_ZH) {
		MERGE_TABLE(table_chinese_japanese_common);
		MERGE_PACKED_TABLE(0x4E00, packed_table_chinese);
	} // zh-simplified
	if (flags & FONT_ZH) {
		MERGE_TABLE(table_chinese_punctuation);
	} // both zh-simplified and zh-full
	//  if(flags & FONT_ZH)    { MERGE_TABLE(table_chinese_full); } // zh-full
	array_sort(sorted, less_64_ptr);
	array_unique(sorted, less_64_ptr); // sort + unique pass

	// pack and create bitmap
	unsigned char *bitmap = (unsigned char *)MALLOC(f->height * f->width);

	int charCount = *array_back(sorted) - sorted[0] + 1; // 0xEFFFF;
	f->cdata = (stbtt_packedchar *)CALLOC(1, sizeof(stbtt_packedchar) * charCount);
	f->iter2cp = (unsigned *)MALLOC(sizeof(unsigned) * charCount);
	f->cp2iter = (unsigned *)MALLOC(sizeof(unsigned) * charCount);
	for (int i = 0; i < charCount; ++i)
		f->iter2cp[i] = f->cp2iter[i] = 0xFFFD; // default invalid glyph

	// find first char
	{
		stbtt_fontinfo info = { 0 };
		stbtt_InitFont(&info, ttf_data, stbtt_GetFontOffsetForIndex(ttf_data, 0));

		for (int i = 0, end = array_count(sorted); i < end; ++i) {
			unsigned glyph = sorted[i];
			if (!stbtt_FindGlyphIndex(&info, glyph))
				continue;
			f->begin = glyph;
			break;
		}
	}

	stbtt_pack_context pc;
	if (!stbtt_PackBegin(&pc, bitmap, f->width, f->height, 0, 1, NULL)) {
		PANIC("Failed to initialize atlas font");
	}
	stbtt_PackSetOversampling(&pc, flags & FONT_OVERSAMPLE_X ? 2 : 1, flags & FONT_OVERSAMPLE_Y ? 2 : 1); /*useful on small fonts*/
	int count = 0;
	for (int i = 0, num = array_count(sorted); i < num; ++i) {
		uint64_t begin = sorted[i], end = sorted[i];
		while (i < (num - 1) && (sorted[i + 1] - sorted[i]) == 1)
			end = sorted[++i];
		//printf("(%d,%d)", (unsigned)begin, (unsigned)end);

		if (begin < f->begin)
			continue;

		if (stbtt_PackFontRange(&pc, ttf_data, 0, f->font_size, begin, end - begin + 1, (stbtt_packedchar *)f->cdata + begin - f->begin)) {
			for (uint64_t cp = begin; cp <= end; ++cp) {
				// unicode->index runtime lookup
				f->cp2iter[cp - f->begin] = count;
				f->iter2cp[count++] = cp;
			}
		} else {
			PRINTF("!Failed to pack atlas font. Likely out of texture mem.");
		}
	}
	stbtt_PackEnd(&pc);
	f->num_glyphs = count;

	assert(f->num_glyphs < charCount);

	array_free(sorted);

	// calculate vertical font metrics
	stbtt_fontinfo info = { 0 };
	stbtt_InitFont(&info, ttf_data, stbtt_GetFontOffsetForIndex(ttf_data, 0));

	int a, d, l;
	if (!stbtt_GetFontVMetricsOS2(&info, &a, &d, &l))
		stbtt_GetFontVMetrics(&info, &a, &d, &l);

	f->ascent = a;
	f->descent = d;
	f->linegap = l;
	f->linedist = (a - d + l);
	f->factor = (f->font_size / (f->ascent - f->descent));

	// save some gpu memory by truncating unused vertical space in atlas texture
	{
		int max_y1 = 0;
		for (int i = 0; i < f->num_glyphs; i++) {
			int cp = f->iter2cp[i];
			if (cp == 0xFFFD)
				continue;
			stbtt_packedchar *cd = &f->cdata[cp - f->begin];
			if (cd->y1 > max_y1) {
				max_y1 = cd->y1;
			}
		}
		// cut away the unused part of the bitmap
		f->height = max_y1 + 1;
	}

	PRINTF("Font atlas size %dx%d (GL_R, %5.2fKiB) (%u glyphs)\n", f->width, f->height, f->width * f->height / 1024.f, f->num_glyphs);

	// vao
	glGenVertexArrays(1, &f->vao);
	glBindVertexArray(f->vao);

	// quad vbo setup, used for glyph vertex positions,
	// just uv coordinates that will be stretched accordingly by the glyphs width and height
	float v[] = { 0, 0, 1, 0, 0, 1, 0, 1, 1, 0, 1, 1 };

	glGenBuffers(1, &f->vbo_quad);
	glBindBuffer(GL_ARRAY_BUFFER, f->vbo_quad);
	glBufferData(GL_ARRAY_BUFFER, sizeof(v), v, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void *)0);
	glVertexAttribDivisor(0, 0);

	// instance vbo setup: for glyph positions, glyph index and color index
	glGenBuffers(1, &f->vbo_instances);
	glBindBuffer(GL_ARRAY_BUFFER, f->vbo_instances);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 4 * FONT_MAX_STRING_LEN, NULL, GL_DYNAMIC_DRAW);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (void *)0);
	glVertexAttribDivisor(1, 1);
	//glEnable(GL_FRAMEBUFFER_SRGB);

	// setup and upload font bitmap texture
	glGenTextures(1, &f->texture_fontdata);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, f->texture_fontdata);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, f->width, f->height, 0, GL_RED, GL_UNSIGNED_BYTE, bitmap);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	// last chance to inspect the font atlases
	if (flag("--font-debug"))
		stbi_write_png(va("font_debug%d.png", index), f->width, f->height, 1, bitmap, 0);

	FREE(bitmap);

	// setup and upload font metadata texture
	// used for lookup in the bitmap texture
	glGenTextures(1, &f->texture_offsets);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, f->texture_offsets);

	float *texture_offsets = (float *)MALLOC(sizeof(float) * 8 * f->num_glyphs);

	// remap larger 0xFFFF unicodes into smaller NUM_GLYPHS glyphs
	for (int i = 0, count = 0; i < f->num_glyphs; i++) {
		unsigned cp = f->iter2cp[i];
		if (cp == 0xFFFD)
			continue;

		stbtt_packedchar *cd = &f->cdata[cp - f->begin];
		//      if(cd->x1==cd->x0) { f->iter2cp[i] = f->cp2iter[cp - f->begin] = 0xFFFD; continue; }

		int k1 = 0 * f->num_glyphs + count;
		int k2 = 1 * f->num_glyphs + count;
		++count;

		texture_offsets[4 * k1 + 0] = cd->x0 / (double)f->width;
		texture_offsets[4 * k1 + 1] = cd->y0 / (double)f->height;
		texture_offsets[4 * k1 + 2] = (cd->x1 - cd->x0) / (double)f->width;
		texture_offsets[4 * k1 + 3] = (cd->y1 - cd->y0) / (double)f->height;

		texture_offsets[4 * k2 + 0] = cd->xoff / (double)f->width;
		texture_offsets[4 * k2 + 1] = cd->yoff / (double)f->height;
		texture_offsets[4 * k2 + 2] = cd->xoff2 / (double)f->width;
		texture_offsets[4 * k2 + 3] = cd->yoff2 / (double)f->height;
	}

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, f->num_glyphs, 2, 0, GL_RGBA, GL_FLOAT, texture_offsets);

	FREE(texture_offsets);

	// setup color texture
	glGenTextures(1, &f->texture_colors);
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_1D, f->texture_colors);
	glTexImage1D(GL_TEXTURE_1D, 0, GL_RGBA, FONT_MAX_COLORS, 0, GL_RGBA, GL_UNSIGNED_BYTE, font_palette);
	glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_WRAP_S, GL_REPEAT);

	// upload constant uniforms
	glUseProgram(f->program);
	glUniform1i(glGetUniformLocation(f->program, "sampler_font"), 0);
	glUniform1i(glGetUniformLocation(f->program, "sampler_meta"), 1);
	glUniform1i(glGetUniformLocation(f->program, "sampler_colors"), 2);

	glUniform2f(glGetUniformLocation(f->program, "res_bitmap"), f->width, f->height);
	glUniform2f(glGetUniformLocation(f->program, "res_meta"), f->num_glyphs, 2);
	glUniform1f(glGetUniformLocation(f->program, "num_colors"), FONT_MAX_COLORS);
	(void)flags;
}

void font_face(const char *tag, const char *filename_ttf, float font_size, unsigned flags) {
	font_init();

	int len;
	const char *buffer = vfs_load(filename_ttf, &len);
	if (!buffer)
		buffer = file_load(filename_ttf, &len);

	font_face_from_mem(tag, buffer, len, font_size, flags);
}

static void font_draw_cmd(font_t *f, const float *glyph_data, int glyph_idx, float factor, vec2 offset) {
	// Backup GL state
	GLint last_program, last_vertex_array;
	GLint last_texture0, last_texture1, last_texture2;
	GLint last_blend_src, last_blend_dst;
	GLint last_blend_equation_rgb, last_blend_equation_alpha;

	glGetIntegerv(GL_CURRENT_PROGRAM, &last_program);
	glGetIntegerv(GL_VERTEX_ARRAY_BINDING, &last_vertex_array);

	glActiveTexture(GL_TEXTURE0);
	glGetIntegerv(GL_TEXTURE_BINDING_2D, &last_texture0);
	glActiveTexture(GL_TEXTURE1);
	glGetIntegerv(GL_TEXTURE_BINDING_2D, &last_texture1);
	glActiveTexture(GL_TEXTURE2);
	glGetIntegerv(GL_TEXTURE_BINDING_1D, &last_texture2);

	glGetIntegerv(GL_BLEND_SRC, &last_blend_src);
	glGetIntegerv(GL_BLEND_DST, &last_blend_dst);
	glGetIntegerv(GL_BLEND_EQUATION_RGB, &last_blend_equation_rgb);
	glGetIntegerv(GL_BLEND_EQUATION_ALPHA, &last_blend_equation_alpha);

	GLboolean last_enable_blend = glIsEnabled(GL_BLEND);
	GLboolean last_enable_depth_test = glIsEnabled(GL_DEPTH_TEST);

	// Setup render state: alpha-blending enabled, no depth testing and bind textures
	glEnable(GL_BLEND);
	glBlendEquation(GL_FUNC_ADD);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glDisable(GL_DEPTH_TEST);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, f->texture_fontdata);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, f->texture_offsets);
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_1D, f->texture_colors);

	// update bindings
	glBindVertexArray(f->vao);

	// update uniforms
	glUseProgram(f->program);
	glUniform1f(glGetUniformLocation(f->program, "scale_factor"), factor);
	glUniform2fv(glGetUniformLocation(f->program, "string_offset"), 1, &offset.x);
	glUniform1f(glGetUniformLocation(f->program, "offset_firstline"), f->ascent * f->factor);

	GLint dims[4] = { 0 };
	glGetIntegerv(GL_VIEWPORT, dims);
	glUniform2f(glGetUniformLocation(f->program, "resolution"), dims[2], dims[3]);

	// actual uploading
	glBindBuffer(GL_ARRAY_BUFFER, f->vbo_instances);
	glBufferSubData(GL_ARRAY_BUFFER, 0, 4 * 4 * glyph_idx, glyph_data);

	// actual drawing
	glDrawArraysInstanced(GL_TRIANGLES, 0, 6, glyph_idx);

	// Restore modified GL state
	glUseProgram(last_program);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, last_texture0);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, last_texture1);
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_1D, last_texture2);

	glBlendEquationSeparate(last_blend_equation_rgb, last_blend_equation_alpha);
	glBindVertexArray(last_vertex_array);
	glBlendFunc(last_blend_src, last_blend_dst);

	(last_enable_depth_test ? glEnable(GL_DEPTH_TEST) : glDisable(GL_DEPTH_TEST));
	(last_enable_blend ? glEnable(GL_BLEND) : glDisable(GL_BLEND));
}

// 1. call font_face() if it's the first time it's called.
// 1. parse the string and update the instance vbo, then upload it
// 1. draw the string
static vec2 font_draw_ex(const char *text, vec2 offset, const char *col, void (*draw_cmd)(font_t *, const float *, int, float, vec2)) {
	font_init();

	// sanity checks
	int len = strlen(text);
	if (len >= FONT_MAX_STRING_LEN) {
		return vec2(0, 0);
	}

	// pre-init
	static __thread float *text_glyph_data;
	do_once text_glyph_data = MALLOC(4 * FONT_MAX_STRING_LEN * sizeof(float));

	// ready
	font_t *f = &fonts[0];
	int S = 3;
	uint32_t color = 0;
	float X = 0, Y = 0, W = 0, L = f->ascent * f->factor * f->scale[S], LL = L; // LL=largest linedist
	offset.y = -offset.y; // invert y polarity

	// utf8 to utf32
	array(uint32_t) unicode = string32(text);

	// parse string
	float *t = text_glyph_data;
	for (int i = 0, end = array_count(unicode); i < end; ++i) {
		uint32_t ch = unicode[i];

		if (ch == '\n') {
			// change cursor, advance y, record largest x as width, increase height
			if (X > W)
				W = X;
			X = 0.0;
			Y -= f->linedist * f->factor * f->scale[S];
			if (i + 1 == end) { //@hack: ensures we terminate the height at the correct position
				Y -= (f->descent + f->linegap) * f->factor * f->scale[S];
			}
			continue;
		}
		if (ch >= 1 && ch <= 6) {
			// flush previous state
			if (draw_cmd)
				draw_cmd(f, text_glyph_data, (t - text_glyph_data) / 4, f->scale[S], offset);
			t = text_glyph_data;

			// reposition offset to align new baseline
			// @fixme:
			// offset.y += (f->linedist - f->linegap) * ( f->scale[ch] - f->scale[S] );

			// change size
			S = ch;
			L = f->ascent * f->factor * f->scale[S];
			if (L > LL)
				LL = L;
			continue;
		}
		if (ch >= 0x1a && ch <= 0x1f) {
			color = ch - 0x1a;
			continue;
		}
		if (ch >= 0x10 && ch <= 0x19) {
			if (fonts[ch - 0x10].initialized) {
				// flush previous state
				if (draw_cmd)
					draw_cmd(f, text_glyph_data, (t - text_glyph_data) / 4, f->scale[S], offset);
				t = text_glyph_data;

				// change face
				f = &fonts[ch - 0x10];
			}
			continue;
		}

		// convert to vbo data
		int cp = ch - f->begin; // f->cp2iter[ch - f->begin];
		//if(cp == 0xFFFD) continue;
		//if (cp > f->num_glyphs) continue;

		*t++ = X;
		*t++ = Y;
		*t++ = f->cp2iter[cp];
		*t++ = col ? col[i] : color;

		X += f->cdata[cp].xadvance * f->scale[S];
	}

	if (draw_cmd)
		draw_cmd(f, text_glyph_data, (t - text_glyph_data) / 4, f->scale[S], offset);

	//if(strstr(text, "fps")) printf("(%f,%f) (%f) L:%f LINEDIST:%f\n", X, Y, W, L, f->linedist);
	return abs2(vec2(W * W > X * X ? W : X, Y * Y > LL * LL ? Y : LL));
}

void *font_colorize(const char *text, const char *comma_types, const char *comma_keywords) {
	// reallocate memory
	static __thread int slot = 0;
	static __thread char *buf[16] = { 0 };
	static __thread array(char *) list[16] = { 0 };

	slot = (slot + 1) % 16;
	buf[slot] = REALLOC(buf[slot], strlen(text) + 1);
	memset(buf[slot], 0, strlen(text) + 1);

	// ready
	char *col = buf[slot];
	char *str = STRDUP(text);

	// split inputs
	array(char *) TYPES = strsplit(comma_types, ", ");
	array(char *) KEYWORDS = strsplit(comma_keywords, ", ");

	// ignored characters
	char delims[] = " ,(){}[];\t\n";
	int num_delims = strlen(delims);

	char operators[] = "/+-*<>=&|";
	int num_operators = strlen(operators);

	struct token {
		char *start, *stop;
		enum {
			TOKEN_OTHER,
			TOKEN_OPERATOR,
			TOKEN_NUMERIC,
			TOKEN_FUNCTION,
			TOKEN_KEYWORD,
			TOKEN_COMMENT,
			TOKEN_VARIABLE,
			TOKEN_UNSET
		} type;
	} tokens[9999]; // hurr
	int num_tokens = 0; // running counter

	char *ptr = str;
	while (*ptr) {
		// skip delimiters
		int is_delim = 0;
		for (int i = 0; i < num_delims; i++) {
			if (*ptr == delims[i]) {
				is_delim = 1;
				break;
			}
		}

		if (is_delim == 1) {
			ptr++;
			continue;
		}

		// found a token!
		char *start = ptr;

		if (*ptr == '/' && *(ptr + 1) == '/') {
			// found a line comment, go to end of line or end of file
			while (*ptr != '\n' && *ptr != '\0') {
				ptr++;
			}

			tokens[num_tokens].start = start;
			tokens[num_tokens].stop = ptr;
			tokens[num_tokens].type = TOKEN_COMMENT;
			num_tokens++;

			ptr++;
			continue;
		}

		if (*ptr == '/' && *(ptr + 1) == '*') {
			// found a block comment, go to end of line or end of file
			while (!(*ptr == '*' && *(ptr + 1) == '/') && *ptr != '\0') {
				ptr++;
			}
			ptr++;

			tokens[num_tokens].start = start;
			tokens[num_tokens].stop = ptr + 1;
			tokens[num_tokens].type = TOKEN_COMMENT;
			num_tokens++;

			ptr++;
			continue;
		}

		// check if it's an operator
		int is_operator = 0;
		for (int i = 0; i < num_operators; i++) {
			if (*ptr == operators[i]) {
				is_operator = 1;
				break;
			}
		}

		if (is_operator == 1) {
			tokens[num_tokens].start = start;
			tokens[num_tokens].stop = ptr + 1;
			tokens[num_tokens].type = TOKEN_OPERATOR;
			num_tokens++;
			ptr++;
			continue;
		}

		// it's either a name, type, a keyword, a function, or an names separated by an operator without spaces
		while (*ptr) {
			// check whether it's an operator stuck between two names
			int is_operator2 = 0;
			for (int i = 0; i < num_operators; i++) {
				if (*ptr == operators[i]) {
					is_operator2 = 1;
					break;
				}
			}

			if (is_operator2 == 1) {
				tokens[num_tokens].start = start;
				tokens[num_tokens].stop = ptr;
				tokens[num_tokens].type = TOKEN_UNSET;
				num_tokens++;
				break;
			}

			// otherwise go until we find the next delimiter
			int is_delim2 = 0;
			for (int i = 0; i < num_delims; i++) {
				if (*ptr == delims[i]) {
					is_delim2 = 1;
					break;
				}
			}

			if (is_delim2 == 1) {
				tokens[num_tokens].start = start;
				tokens[num_tokens].stop = ptr;
				tokens[num_tokens].type = TOKEN_UNSET;
				num_tokens++;
				ptr++;
				break;
			}

			// did not find delimiter, check next char
			ptr++;
		}
	}

	// determine the types of the unset tokens, i.e. either
	// a name, a type, a keyword, or a function
	int num_keywords = array_count(KEYWORDS);
	int num_types = array_count(TYPES);

	for (int i = 0; i < num_tokens; i++) {
		// TOKEN_OPERATOR and TOKEN_COMMENT should already be set, so skip those
		if (tokens[i].type != TOKEN_UNSET) {
			continue;
		}

		char end_char = *tokens[i].stop;

		// temporarily null terminate at end of token, restored after parsing
		*tokens[i].stop = '\0';

		// parse

		// if it's a keyword
		int is_keyword = 0;
		for (int j = 0; j < num_keywords; j++) {
			if (strcmp(tokens[i].start, KEYWORDS[j]) == 0) {
				is_keyword = 1;
				break;
			}
		}
		if (is_keyword == 1) {
			tokens[i].type = TOKEN_KEYWORD;
			*tokens[i].stop = end_char;
			continue;
		}

		// Check if it's a function
		float f;
		if (end_char == '(') {
			tokens[i].type = TOKEN_FUNCTION;
			*tokens[i].stop = end_char;
			continue;
		}

		// or if it's a numeric value. catches both integers and floats
		if (sscanf(tokens[i].start, "%f", &f) == 1) {
			tokens[i].type = TOKEN_NUMERIC;
			*tokens[i].stop = end_char;
			continue;
		}

		// if it's a variable type
		int is_type = 0;
		for (int j = 0; j < num_types; j++) {
			if (strcmp(tokens[i].start, TYPES[j]) == 0) {
				is_type = 1;
				break;
			}
		}
		if (is_type == 1) {
			tokens[i].type = TOKEN_VARIABLE;
			*tokens[i].stop = end_char;
			continue;
		}

		// otherwise it's a regular variable name
		tokens[i].type = TOKEN_OTHER;
		*tokens[i].stop = end_char;
	}

	// print all tokens and their types
	for (int i = 0; i < num_tokens; i++) {
		for (char *p = tokens[i].start; p != tokens[i].stop; p++) {
			col[(p - str)] = tokens[i].type;
		}
	}

	FREE(str);
	return col;
}

static vec2 gotoxy = { 0 };

// Return cursor
vec2 font_xy() {
	return gotoxy;
}

// Relocate cursor
void font_goto(float x, float y) {
	gotoxy = vec2(x, y);
}

// Print and linefeed. Text may include markup code
vec2 font_print(const char *text) {
	// @fixme: remove this hack
	if (text[0] == FONT_LEFT[0]) {
		int l = text[1] == FONT_LEFT[1];
		int c = text[1] == FONT_CENTER[1];
		int r = text[1] == FONT_RIGHT[1];
		if (l || c || r) {
			vec2 rect = font_rect(text + 2);
			gotoxy.x = l ? 0 : r ? (window_width() - rect.x)
								 : window_width() / 2 - rect.x / 2;
			return font_print(text + 2);
		}
		int t = text[1] == FONT_TOP[1];
		int b = text[1] == FONT_BOTTOM[1];
		int m = text[1] == FONT_MIDDLE[1];
		int B = text[1] == FONT_BASELINE[1];
		if (t || b || m || B) {
			vec2 rect = font_rect(text + 2);
			gotoxy.y = t ? 0 : b ? (window_height() - rect.y)
					: m			 ? window_height() / 2 - rect.y / 2
								 : window_height() / 2 - rect.y / 1;
			return font_print(text + 2);
		}
	}

	vec2 dims = font_draw_ex(text, gotoxy, NULL, font_draw_cmd);
	gotoxy.y += strchr(text, '\n') ? dims.y : 0;
	gotoxy.x = strchr(text, '\n') ? 0 : gotoxy.x + dims.x;
	return dims;
}

// Print a code snippet with syntax highlighting
vec2 font_highlight(const char *text, const void *colors) {
	vec2 dims = font_draw_ex(text, gotoxy, (const char *)colors, font_draw_cmd);
	gotoxy.y += strchr(text, '\n') ? dims.y : 0;
	gotoxy.x = strchr(text, '\n') ? 0 : gotoxy.x + dims.x;
	return dims;
}

// Calculate the size of a string, in the pixel size specified. Count stray newlines too.
vec2 font_rect(const char *str) {
	return font_draw_ex(str, gotoxy, NULL, NULL);
}

font_metrics_t font_metrics(const char *text) {
	font_metrics_t m = { 0 };
	int S = 3;
	font_t *f = &fonts[0];

	// utf8 to utf32
	array(uint32_t) unicode = string32(text);

	// parse string
	for (int i = 0, end = array_count(unicode); i < end; ++i) {
		uint32_t ch = unicode[i];
		if (ch >= 1 && ch <= 6) {
			S = ch;
			continue;
		}
		if (ch >= 0x1a && ch <= 0x1f) {
			if (fonts[ch - 0x1a].initialized) {
				// change face
				f = &fonts[ch - 0x1a];
			}
			continue;
		}
	}

	m.ascent = f->ascent * f->factor * f->scale[S];
	m.descent = f->descent * f->factor * f->scale[S];
	m.linegap = f->linegap * f->factor * f->scale[S];
	m.linedist = f->linedist * f->factor * f->scale[S];
	return m;
}

TextRenderer *TextRenderer::get_singleton();

TextRenderer *TextRenderer::_singleton;
