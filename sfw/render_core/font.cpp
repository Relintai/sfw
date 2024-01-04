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

#include "font.h"

#include "window.h"

#include "3rd_glad.h"
#define STB_TRUETYPE_IMPLEMENTATION
#include "3rd_stb_truetype.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#include "font_data_bm_mini.inc.h"
#include "font_data_tables.inc.h"

#include "render_core/image.h"
#include "render_core/texture.h"

void Font::load_default(const float size, const uint32_t flags) {
	font_face_from_mem(bm_mini_ttf, 20176, size, flags);
}

float Font::get_scale() const {
	return _scale;
}
void Font::set_scale(const float p_scale) {
	_scale = p_scale;
}

void Font::font_face_from_mem(const void *ttf_data, uint32_t ttf_len, float font_size, uint32_t flags) {
	if (font_size <= 0 || font_size > 72) {
		return;
	}

	if (!ttf_data || !ttf_len) {
		return;
	}

	if (!(flags & FONT_ASCII)) {
		flags |= FONT_ASCII; // ensure this minimal range [0020-00FF] is almost always in
	}

	_initialized = 1;

	// load .ttf into a bitmap using stb_truetype.h
	int dim = flags & FONT_4096 ? 4096 : flags & FONT_2048 ? 2048
			: flags & FONT_1024							   ? 1024
														   : 512;
	_width = dim;
	_height = dim;

	// change size [h1(largest) to h3(regular) to h6(smallest)]
	_font_size = font_size;
	_scale = 1.0000f;

// figure out what ranges we're about to bake
#define MERGE_TABLE(table)                                     \
	do {                                                       \
		for (unsigned i = 0; table[i]; i += 2) {               \
			uint64_t begin = table[i + 0], end = table[i + 1]; \
			for (unsigned j = begin; j <= end; ++j) {          \
				sorted.push_back(j);                           \
			}                                                  \
		}                                                      \
	} while (0)

#define MERGE_PACKED_TABLE(codepoint_begin, table, table_size)                     \
	do {                                                                           \
		for (int i = 0, begin = codepoint_begin, end = table_size; i < end; i++) { \
			sorted.push_back((unsigned)(begin + table[i]));                        \
			begin += table[i];                                                     \
		}                                                                          \
	} while (0)

	Vector<uint64_t> sorted;
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
		MERGE_PACKED_TABLE(0x4E00, packed_table_japanese, 2999);
	}
	if (flags & FONT_ZH) {
		MERGE_TABLE(table_chinese_japanese_common);
		MERGE_PACKED_TABLE(0x4E00, packed_table_chinese, 2500);

	} // zh-simplified
	if (flags & FONT_ZH) {
		MERGE_TABLE(table_chinese_punctuation);
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
	//unsigned char *bitmap = memnew_arr(unsigned char, _height * _width);
	Vector<uint8_t> bitmap_data;
	bitmap_data.resize(_height * _width);
	unsigned char *bitmap = (unsigned char *)bitmap_data.ptrw();

	int charCount = sorted[sorted.size() - 1] - sorted[0] + 1; // 0xEFFFF;
	_cdata = (stbtt_packedchar *)calloc(1, sizeof(stbtt_packedchar) * charCount);
	_iter2cp = memnew_arr(unsigned int, charCount);
	_cp2iter = memnew_arr(unsigned int, charCount);
	for (int i = 0; i < charCount; ++i) {
		_iter2cp[i] = _cp2iter[i] = 0xFFFD; // default invalid glyph
	}

	// find first ch./co
	{
		stbtt_fontinfo info = { 0 };
		stbtt_InitFont(&info, (const unsigned char *)ttf_data, stbtt_GetFontOffsetForIndex((const unsigned char *)ttf_data, 0));

		for (int i = 0, end = sorted.size() - 1; i < end; ++i) {
			unsigned glyph = sorted[i];
			if (!stbtt_FindGlyphIndex(&info, glyph))
				continue;
			_begin = glyph;
			break;
		}
	}

	stbtt_pack_context pc;
	if (!stbtt_PackBegin(&pc, bitmap, _width, _height, 0, 1, NULL)) {
		ERR_FAIL_COND("Failed to initialize atlas font");
	}
	stbtt_PackSetOversampling(&pc, flags & FONT_OVERSAMPLE_X ? 2 : 1, flags & FONT_OVERSAMPLE_Y ? 2 : 1); /*useful on small fonts*/
	unsigned int count = 0;
	for (int i = 0, num = sorted.size() - 1; i < num; ++i) {
		uint64_t begin = sorted[i], end = sorted[i];
		while (i < (num - 1) && (sorted[i + 1] - sorted[i]) == 1) {
			end = sorted[++i];
		}
		//printf("(%d,%d)", (unsigned)begin, (unsigned)end);

		if (begin < _begin)
			continue;

		if (stbtt_PackFontRange(&pc, (const unsigned char *)ttf_data, 0, _font_size, begin, end - begin + 1, (stbtt_packedchar *)_cdata + begin - _begin)) {
			for (uint64_t cp = begin; cp <= end; ++cp) {
				// unicode->index runtime lookup
				_cp2iter[cp - _begin] = count;
				_iter2cp[count++] = cp;
			}
		} else {
			ERR_PRINT("!Failed to pack atlas font. Likely out of texture mem.");
		}
	}
	stbtt_PackEnd(&pc);
	_num_glyphs = count;

	// calculate vertical font metrics
	stbtt_fontinfo info = { 0 };
	stbtt_InitFont(&info, (const unsigned char *)ttf_data, stbtt_GetFontOffsetForIndex((const unsigned char *)ttf_data, 0));

	int a, d, l;
	if (!stbtt_GetFontVMetricsOS2(&info, &a, &d, &l)) {
		stbtt_GetFontVMetrics(&info, &a, &d, &l);
	}

	_ascent = a;
	_descent = d;
	_linegap = l;
	_linedist = (a - d + l);
	_factor = (_font_size / (_ascent - _descent));

	// save some gpu memory by truncating unused vertical space in atlas texture
	{
		int max_y1 = 0;
		for (unsigned int i = 0; i < _num_glyphs; i++) {
			int cp = _iter2cp[i];
			if (cp == 0xFFFD)
				continue;
			stbtt_packedchar *cd = &_cdata[cp - _begin];
			if (cd->y1 > max_y1) {
				max_y1 = cd->y1;
			}
		}
		// cut away the unused part of the bitmap
		_height = max_y1 + 1;
	}

	//LOG_MSG("Font atlas size %dx%d (GL_R, %5.2fKiB) (%u glyphs)\n", _width, _height, _width * _height / 1024.f, _num_glyphs);

	/*
	// setup and upload font bitmap texture
	glGenTextures(1, &f->texture_fontdata);
	glBindTexture(GL_TEXTURE_2D, f->texture_fontdata);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, _width, _height, 0, GL_RED, GL_UNSIGNED_BYTE, bitmap);
	*/

	// last chance to inspect the font atlases
	//if (flag("--font-debug"))
	//String pngname = "font_debug" + itos(index) + " .png";
	//stbi_write_png(pngname.utf8().get_data(), _width, _height, 1, bitmap, 0);

	if (!_image.is_valid()) {
		_image.instance();
	}

	bitmap_data.resize(_width * _height);

	_image->create(_width, _height, false, Image::FORMAT_L8, bitmap_data);

	if (!_texture.is_valid()) {
		_texture.instance();
	}

	_texture->create_from_image(_image);

	_texture_offsets.resize(_num_glyphs);

	// remap larger 0xFFFF unicodes into smaller NUM_GLYPHS glyphs
	for (unsigned i = 0; i < _num_glyphs; i++) {
		unsigned cp = _iter2cp[i];
		if (cp == 0xFFFD) {
			continue;
		}

		stbtt_packedchar *cd = &_cdata[cp - _begin];
		//      if(cd->x1==cd->x0) { _iter2cp[i] = _cp2iter[cp - _begin] = 0xFFFD; continue; }

		TextureOffset offset;

		offset.x = cd->x0 / (double)_width;
		offset.y = cd->y0 / (double)_height;
		offset.w = (cd->x1 - cd->x0) / (double)_width;
		offset.h = (cd->y1 - cd->y0) / (double)_height;

		offset.xoff = cd->xoff / (double)_width;
		offset.yoff = cd->yoff / (double)_height;
		offset.woff = cd->xoff2 / (double)_width;
		offset.hoff = cd->yoff2 / (double)_height;

		_texture_offsets.write[i] = offset;
	}

	/*
	float *texture_offsets = memnew_arr(float, 8 * _num_glyphs);

	// remap larger 0xFFFF unicodes into smaller NUM_GLYPHS glyphs
	for (unsigned i = 0, count = 0; i < _num_glyphs; i++) {
		unsigned cp = _iter2cp[i];
		if (cp == 0xFFFD)
			continue;

		stbtt_packedchar *cd = &_cdata[cp - _begin];
		//      if(cd->x1==cd->x0) { _iter2cp[i] = _cp2iter[cp - _begin] = 0xFFFD; continue; }

		int k1 = 0 * _num_glyphs + count;
		int k2 = 1 * _num_glyphs + count;
		++count;

		texture_offsets[4 * k1 + 0] = cd->x0 / (double)_width;
		texture_offsets[4 * k1 + 1] = cd->y0 / (double)_height;
		texture_offsets[4 * k1 + 2] = (cd->x1 - cd->x0) / (double)_width;
		texture_offsets[4 * k1 + 3] = (cd->y1 - cd->y0) / (double)_height;

		texture_offsets[4 * k2 + 0] = cd->xoff / (double)_width;
		texture_offsets[4 * k2 + 1] = cd->yoff / (double)_height;
		texture_offsets[4 * k2 + 2] = cd->xoff2 / (double)_width;
		texture_offsets[4 * k2 + 3] = cd->yoff2 / (double)_height;
	}

	glUniform1i(glGetUniformLocation(f->program->get_program(), "sampler_font"), 0);
	glUniform1i(glGetUniformLocation(f->program->get_program(), "sampler_meta"), 1);
	glUniform1i(glGetUniformLocation(f->program->get_program(), "sampler_colors"), 2);

	glUniform2f(glGetUniformLocation(f->program->get_program(), "res_bitmap"), _width, _height);
	glUniform2f(glGetUniformLocation(f->program->get_program(), "res_meta"), _num_glyphs, 2);
	glUniform1f(glGetUniformLocation(f->program->get_program(), "num_colors"), FONT_MAX_COLORS);
	(void)flags;
	*/
}

void Font::font_face(const char *filename_ttf, float font_size, unsigned flags) {
	/*
	font_init();

	int len;
	const char *buffer = vfs_load(filename_ttf, &len);
	if (!buffer)
		buffer = file_load(filename_ttf, &len);

	font_face_from_mem(tag, buffer, len, font_size, flags);
	*/
}

void Font::font_draw_cmd(const float *glyph_data, int glyph_idx, float factor, Vector2 offset) {
	/*
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
	glUniform1f(glGetUniformLocation(f->program->get_program(), "offset_firstline"), _ascent * _factor);

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
	*/
}

// 1. call font_face() if it's the first time it's called.
// 1. parse the string and update the instance vbo, then upload it
// 1. draw the string
Vector2 Font::font_draw_ex(const String &text, Vector2 offset, const char *col, void (*draw_cmd)(const float *, int, float, Vector2)) {
	/*
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
	float X = 0, Y = 0, W = 0, L = _ascent * _factor * _scale[S], LL = L; // LL=largest linedist
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
			Y -= _linedist * _factor * _scale[S];
			if (i + 1 == end) { //@hack: ensures we terminate the height at the correct position
				Y -= (_descent + _linegap) * _factor * _scale[S];
			}
			continue;
		}
		if (ch >= 1 && ch <= 6) {
			// flush previous state
			if (draw_cmd)
				draw_cmd(f, text_glyph_data, (t - text_glyph_data) / 4, _scale[S], offset);
			t = text_glyph_data;

			// reposition offset to align new baseline
			// @fixme:
			// offset.y += (_linedist - _linegap) * ( _scale[ch] - _scale[S] );

			// change size
			S = ch;
			L = _ascent * _factor * _scale[S];
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
					draw_cmd(f, text_glyph_data, (t - text_glyph_data) / 4, _scale[S], offset);
				t = text_glyph_data;

				// change face
				f = &fonts[ch - 0x10];
			}
			continue;
		}

		// convert to vbo data
		int cp = ch - _begin; // _cp2iter[ch - _begin];
		//if(cp == 0xFFFD) continue;
		//if (cp > _num_glyphs) continue;

		*t++ = X;
		*t++ = Y;
		*t++ = _cp2iter[cp];
		*t++ = col ? col[i] : color;

		X += _cdata[cp].xadvance * _scale[S];
	}

	if (draw_cmd)
		draw_cmd(f, text_glyph_data, (t - text_glyph_data) / 4, _scale[S], offset);

	//if(strstr(text, "fps")) printf("(%f,%f) (%f) L:%f LINEDIST:%f\n", X, Y, W, L, _linedist);
	return Vector2(W * W > X * X ? W : X, Y * Y > LL * LL ? Y : LL).abs();
	*/

	return Vector2();
}

// Return cursor
Vector2 Font::font_xy() {
	return gotoxy;
}

// Relocate cursor
void Font::font_goto(float x, float y) {
	gotoxy = Vector2(x, y);
}

// Calculate the size of a string, in the pixel size specified. Count stray newlines too.
Vector2 Font::font_rect(const String &str) {
	return font_draw_ex(str, gotoxy, NULL, NULL);
}

Font::font_metrics_t Font::font_metrics(const String &text) {
	font_metrics_t m = { 0 };

	/*

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

	*/

	m.ascent = _ascent * _factor * _scale;
	m.descent = _descent * _factor * _scale;
	m.linegap = _linegap * _factor * _scale;
	m.linedist = _linedist * _factor * _scale;

	return m;
}

int Font::get_atlas_width() {
	return _width;
}

int Font::get_atlas_height() {
	return _height;
}

Ref<Image> Font::get_image() {
	return _image;
}
Ref<Texture> Font::get_texture() {
	return _texture;
}

Font::Font() {
	_initialized = false;
}
