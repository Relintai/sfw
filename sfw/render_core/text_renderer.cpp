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

#include "text_renderer.h"

#include "window.h"

#include "3rd_glad.h"
#define STB_TRUETYPE_IMPLEMENTATION
#include "3rd_stb_truetype.h"

#include "font_data_bm_mini.inc.h"

#define RGB4(r, g, b, a) ((((uint32_t)a) << 24) | (((uint32_t)b) << 16) | (((uint32_t)g) << 8) | ((uint32_t)r))

uint32_t TextRenderer::font_palette[FONT_MAX_COLORS] = {
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

void TextRenderer::font_init() {
	if (_fonts_initialized) {
		return;
	}

	_fonts_initialized = true;

	font_face_from_mem(FONT_FACE1, bm_mini_ttf, 20176, 42.5f, 0);
	font_face_from_mem(FONT_FACE2, bm_mini_ttf, 20176, 42.5f, 0);
	font_face_from_mem(FONT_FACE3, bm_mini_ttf, 20176, 42.5f, 0);
	font_face_from_mem(FONT_FACE4, bm_mini_ttf, 20176, 42.5f, 0);
	font_face_from_mem(FONT_FACE5, bm_mini_ttf, 20176, 42.5f, 0);
	font_face_from_mem(FONT_FACE6, bm_mini_ttf, 20176, 42.5f, 0);
	font_face_from_mem(FONT_FACE7, bm_mini_ttf, 20176, 42.5f, 0);
	font_face_from_mem(FONT_FACE8, bm_mini_ttf, 20176, 42.5f, 0);
	font_face_from_mem(FONT_FACE9, bm_mini_ttf, 20176, 42.5f, 0);
	font_face_from_mem(FONT_FACE10, bm_mini_ttf, 20176, 42.5f, 0);
}

// Remap color within all existing color textures
void TextRenderer::font_color(const char *tag, uint32_t color) {
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

void TextRenderer::font_scales(const char *tag, float h1, float h2, float h3, float h4, float h5, float h6) {
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
void TextRenderer::font_face_from_mem(const char *tag, const void *ttf_data, unsigned ttf_len, float font_size, unsigned flags) {
	unsigned index = *tag - FONT_FACE1[0];
	if (index > FONTS_MAX) {
		return;
	}

	if (font_size <= 0 || font_size > 72) {
		return;
	}

	if (!ttf_data || !ttf_len) {
		return;
	}

	if (!(flags & FONT_EM)) {
		flags |= FONT_ASCII; // ensure this minimal range [0020-00FF] is almost always in
	}

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

	//f->program = shader(vs, fs, "vertexPosition,instanceGlyph", "outColor", NULL);

	f->program.instance();

// figure out what ranges we're about to bake
#define MERGE_TABLE(table, table_size)     \
	int orig_size = sorted.size();         \
	sorted.resize(orig_size + table_size); \
                                           \
	uint64_t *p = sorted.ptrw();           \
                                           \
	for (int i = 0; i < table_size; ++i) { \
		p[orig_size + i] = table[i];       \
	}

#define MERGE_PACKED_TABLE(codepoint_begin, table, table_size) \
	int orig_size = sorted.size();                             \
	int begin = codepoint_begin;                               \
	sorted.resize(orig_size + table_size);                     \
                                                               \
	uint64_t *p = sorted.ptrw();                               \
                                                               \
	for (int i = 0; i < table_size; ++i) {                     \
		p[orig_size + i] = (unsigned)(begin + table[i]);       \
		begin += table[i];                                     \
	}

	Vector<uint64_t> sorted;
	if (flags & FONT_ASCII) {
		MERGE_TABLE(table_common, 5);
	}
	if (flags & FONT_EM) {
		MERGE_TABLE(table_emoji, 7);
	}
	if (flags & FONT_EU) {
		MERGE_TABLE(table_eastern_europe, 19);
	}
	if (flags & FONT_RU) {
		MERGE_TABLE(table_western_europe, 15);
	}
	if (flags & FONT_EL) {
		MERGE_TABLE(table_western_europe, 15);
	}
	if (flags & FONT_AR) {
		MERGE_TABLE(table_middle_east, 7);
	}
	if (flags & FONT_HE) {
		MERGE_TABLE(table_middle_east, 7);
	}
	if (flags & FONT_TH) {
		MERGE_TABLE(table_thai, 5);
	}
	if (flags & FONT_VI) {
		MERGE_TABLE(table_vietnamese, 15);
	}
	if (flags & FONT_KR) {
		MERGE_TABLE(table_korean, 7);
	}
	if (flags & FONT_JP) {
		{
			MERGE_TABLE(table_chinese_japanese_common, 7);
		}
		{
			MERGE_PACKED_TABLE(0x4E00, packed_table_japanese, 2999);
		}
	}
	if (flags & FONT_ZH) {
		{
			MERGE_TABLE(table_chinese_japanese_common, 7);
		}
		{
			MERGE_PACKED_TABLE(0x4E00, packed_table_chinese, 2500);
		}
	} // zh-simplified
	if (flags & FONT_ZH) {
		MERGE_TABLE(table_chinese_punctuation, 3);
	} // both zh-simplified and zh-full
	//  if(flags & FONT_ZH)    { MERGE_TABLE(table_chinese_full); } // zh-full

	sorted.sort();

	for (int i = 0; i < sorted.size(); ++i) {
		uint64_t current_element = sorted[i];

		for (int j = i + 1; j < sorted.size(); ++j) {
			if (sorted[j] == current_element) {
				sorted.remove(j);
				--j;
			} else {
				break;
			}
		}
	}

	// pack and create bitmap
	unsigned char *bitmap = memnew_arr(unsigned char, f->height * f->width);

	int charCount = sorted[sorted.size() - 1] - sorted[0] + 1; // 0xEFFFF;
	f->cdata = (stbtt_packedchar *)calloc(1, sizeof(stbtt_packedchar) * charCount);
	f->iter2cp = memnew_arr(unsigned, charCount);
	f->cp2iter = memnew_arr(unsigned, charCount);
	for (int i = 0; i < charCount; ++i) {
		f->iter2cp[i] = f->cp2iter[i] = 0xFFFD; // default invalid glyph
	}

	// find first char
	{
		stbtt_fontinfo info = { 0 };
		stbtt_InitFont(&info, (const unsigned char *)ttf_data, stbtt_GetFontOffsetForIndex((const unsigned char *)ttf_data, 0));

		for (int i = 0, end = sorted.size(); i < end; ++i) {
			unsigned glyph = sorted[i];
			if (!stbtt_FindGlyphIndex(&info, glyph))
				continue;
			f->begin = glyph;
			break;
		}
	}

	stbtt_pack_context pc;
	if (!stbtt_PackBegin(&pc, bitmap, f->width, f->height, 0, 1, NULL)) {
		ERR_FAIL_COND("Failed to initialize atlas font");
	}
	stbtt_PackSetOversampling(&pc, flags & FONT_OVERSAMPLE_X ? 2 : 1, flags & FONT_OVERSAMPLE_Y ? 2 : 1); /*useful on small fonts*/
	int count = 0;
	for (int i = 0, num = sorted.size(); i < num; ++i) {
		uint64_t begin = sorted[i], end = sorted[i];
		while (i < (num - 1) && (sorted[i + 1] - sorted[i]) == 1) {
			end = sorted[++i];
		}
		//printf("(%d,%d)", (unsigned)begin, (unsigned)end);

		if (begin < f->begin)
			continue;

		if (stbtt_PackFontRange(&pc, (const unsigned char *)ttf_data, 0, f->font_size, begin, end - begin + 1, (stbtt_packedchar *)f->cdata + begin - f->begin)) {
			for (uint64_t cp = begin; cp <= end; ++cp) {
				// unicode->index runtime lookup
				f->cp2iter[cp - f->begin] = count;
				f->iter2cp[count++] = cp;
			}
		} else {
			ERR_PRINT("!Failed to pack atlas font. Likely out of texture mem.");
		}
	}
	stbtt_PackEnd(&pc);
	f->num_glyphs = count;

	//CRASH_COND(f->num_glyphs < (unsigned int)charCount);

	// calculate vertical font metrics
	stbtt_fontinfo info = { 0 };
	stbtt_InitFont(&info, (const unsigned char *)ttf_data, stbtt_GetFontOffsetForIndex((const unsigned char *)ttf_data, 0));

	int a, d, l;
	if (!stbtt_GetFontVMetricsOS2(&info, &a, &d, &l)) {
		stbtt_GetFontVMetrics(&info, &a, &d, &l);
	}

	f->ascent = a;
	f->descent = d;
	f->linegap = l;
	f->linedist = (a - d + l);
	f->factor = (f->font_size / (f->ascent - f->descent));

	// save some gpu memory by truncating unused vertical space in atlas texture
	{
		int max_y1 = 0;
		for (unsigned int i = 0; i < f->num_glyphs; i++) {
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

	LOG_MSG("Font atlas size %dx%d (GL_R, %5.2fKiB) (%u glyphs)\n", f->width, f->height, f->width * f->height / 1024.f, f->num_glyphs);

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
	//if (flag("--font-debug"))
	//	stbi_write_png(va("font_debug%d.png", index), f->width, f->height, 1, bitmap, 0);

	memfree(bitmap);

	// setup and upload font metadata texture
	// used for lookup in the bitmap texture
	glGenTextures(1, &f->texture_offsets);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, f->texture_offsets);

	float *texture_offsets = memnew_arr(float, 8 * f->num_glyphs);

	// remap larger 0xFFFF unicodes into smaller NUM_GLYPHS glyphs
	for (unsigned i = 0, count = 0; i < f->num_glyphs; i++) {
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

	memfree(texture_offsets);

	// setup color texture
	glGenTextures(1, &f->texture_colors);
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_1D, f->texture_colors);
	glTexImage1D(GL_TEXTURE_1D, 0, GL_RGBA, FONT_MAX_COLORS, 0, GL_RGBA, GL_UNSIGNED_BYTE, font_palette);
	glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_WRAP_S, GL_REPEAT);

	// upload constant uniforms
	glUseProgram(f->program->get_program());
	glUniform1i(glGetUniformLocation(f->program->get_program(), "sampler_font"), 0);
	glUniform1i(glGetUniformLocation(f->program->get_program(), "sampler_meta"), 1);
	glUniform1i(glGetUniformLocation(f->program->get_program(), "sampler_colors"), 2);

	glUniform2f(glGetUniformLocation(f->program->get_program(), "res_bitmap"), f->width, f->height);
	glUniform2f(glGetUniformLocation(f->program->get_program(), "res_meta"), f->num_glyphs, 2);
	glUniform1f(glGetUniformLocation(f->program->get_program(), "num_colors"), FONT_MAX_COLORS);
	(void)flags;
}

void TextRenderer::font_face(const char *tag, const char *filename_ttf, float font_size, unsigned flags) {
	/*
	font_init();

	int len;
	const char *buffer = vfs_load(filename_ttf, &len);
	if (!buffer)
		buffer = file_load(filename_ttf, &len);

	font_face_from_mem(tag, buffer, len, font_size, flags);
	*/
}

void TextRenderer::font_draw_cmd(font_t *f, const float *glyph_data, int glyph_idx, float factor, Vector2 offset) {
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
	glUseProgram(f->program->get_program());
	glUniform1f(glGetUniformLocation(f->program->get_program(), "scale_factor"), factor);
	glUniform2fv(glGetUniformLocation(f->program->get_program(), "string_offset"), 1, &offset.x);
	glUniform1f(glGetUniformLocation(f->program->get_program(), "offset_firstline"), f->ascent * f->factor);

	GLint dims[4] = { 0 };
	glGetIntegerv(GL_VIEWPORT, dims);
	glUniform2f(glGetUniformLocation(f->program->get_program(), "resolution"), dims[2], dims[3]);

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
Vector2 TextRenderer::font_draw_ex(const String &text, Vector2 offset, const char *col, void (*draw_cmd)(font_t *, const float *, int, float, Vector2)) {
	font_init();

	// sanity checks
	int len = text.length();
	if (len >= FONT_MAX_STRING_LEN) {
		return Vector2(0, 0);
	}

	// pre-init
	static __thread float *text_glyph_data = NULL;
	if (!text_glyph_data) {
		text_glyph_data = memnew_arr(float, 4 * FONT_MAX_STRING_LEN);
	}

	// ready
	font_t *f = &fonts[0];
	int S = 3;
	uint32_t color = 0;
	float X = 0, Y = 0, W = 0, L = f->ascent * f->factor * f->scale[S], LL = L; // LL=largest linedist
	offset.y = -offset.y; // invert y polarity

	// parse string
	float *t = text_glyph_data;
	for (int i = 0, end = text.length(); i < end; ++i) {
		uint32_t ch = text[i];

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
	return Vector2(W * W > X * X ? W : X, Y * Y > LL * LL ? Y : LL).abs();
}

// Return cursor
Vector2 TextRenderer::font_xy() {
	return gotoxy;
}

// Relocate cursor
void TextRenderer::font_goto(float x, float y) {
	gotoxy = Vector2(x, y);
}

// Print and linefeed. Text may include markup code
Vector2 TextRenderer::font_print(const String &text) {
	// @fixme: remove this hack
	if (text[0] == FONT_LEFT[0]) {
		int window_width = AppWindow::get_singleton()->get_width();
		int window_height = AppWindow::get_singleton()->get_height();

		int l = text[1] == FONT_LEFT[1];
		int c = text[1] == FONT_CENTER[1];
		int r = text[1] == FONT_RIGHT[1];
		if (l || c || r) {
			String ntext = text.substr(2);

			Vector2 rect = font_rect(ntext);
			gotoxy.x = l ? 0 : r ? (window_width - rect.x)
								 : window_width / 2 - rect.x / 2;
			return font_print(ntext);
		}
		int t = text[1] == FONT_TOP[1];
		int b = text[1] == FONT_BOTTOM[1];
		int m = text[1] == FONT_MIDDLE[1];
		int B = text[1] == FONT_BASELINE[1];
		if (t || b || m || B) {
			String ntext = text.substr(2);

			Vector2 rect = font_rect(ntext);
			gotoxy.y = t ? 0 : b ? (window_height - rect.y)
					: m			 ? window_height / 2 - rect.y / 2
								 : window_height / 2 - rect.y / 1;
			return font_print(ntext);
		}
	}

	Vector2 dims = font_draw_ex(text, gotoxy, NULL, font_draw_cmd);

	int nindex = text.find_char('\n');

	gotoxy.y += nindex ? dims.y : 0;
	gotoxy.x = nindex ? 0 : gotoxy.x + dims.x;
	return dims;
}

// Calculate the size of a string, in the pixel size specified. Count stray newlines too.
Vector2 TextRenderer::font_rect(const String &str) {
	return font_draw_ex(str, gotoxy, NULL, NULL);
}

TextRenderer::font_metrics_t TextRenderer::font_metrics(const String &text) {
	font_metrics_t m = { 0 };
	int S = 3;
	font_t *f = &fonts[0];

	// parse string
	for (int i = 0, end = text.length(); i < end; ++i) {
		uint32_t ch = text[i];
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

TextRenderer *TextRenderer::get_singleton() {
	return _singleton;
}

TextRenderer::TextRenderer() {
	_singleton = this;
	_fonts_initialized = false;
}

TextRenderer *TextRenderer::_singleton = NULL;
