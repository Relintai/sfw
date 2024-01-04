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

#include "font_data_bm_mini.inc.h"
#include "font_data_tables.inc.h"

#include "render_core/image.h"
#include "render_core/mesh.h"
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

	unload();

	if (!(flags & FONT_ASCII)) {
		flags |= FONT_ASCII; // ensure this minimal range [0020-00FF] is almost always in
	}

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
	Vector<uint8_t> bitmap_data;
	bitmap_data.resize(_height * _width);
	unsigned char *bitmap = (unsigned char *)bitmap_data.ptrw();

	int charCount = sorted[sorted.size() - 1] - sorted[0] + 1; // 0xEFFFF;
	stbtt_packedchar *cdata = memnew_arr(stbtt_packedchar, charCount);
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
			if (!stbtt_FindGlyphIndex(&info, glyph)) {
				continue;
			}

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

		if (begin < _begin) {
			continue;
		}

		if (stbtt_PackFontRange(&pc, (const unsigned char *)ttf_data, 0, _font_size, begin, end - begin + 1, cdata + begin - _begin)) {
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
			if (cp == 0xFFFD) {
				continue;
			}

			stbtt_packedchar *cd = &cdata[cp - _begin];
			if (cd->y1 > max_y1) {
				max_y1 = cd->y1;
			}
		}
		// cut away the unused part of the bitmap
		_height = max_y1 + 1;
	}

	// last chance to inspect the original font atlases
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

		stbtt_packedchar *cd = &cdata[cp - _begin];

		TextureOffset offset;

		offset.x0 = cd->x0 / (double)_width;
		offset.y0 = cd->y0 / (double)_height;
		offset.x1 = cd->x1 / (double)_width;
		offset.y1 = cd->y1 / (double)_height;

		offset.x0_orig = cd->x0;
		offset.y0_orig = cd->y0;
		offset.x1_orig = cd->x1;
		offset.y1_orig = cd->y1;

		offset.xoff = cd->xoff;
		offset.yoff = cd->yoff;
		offset.xoff2 = cd->xoff2;
		offset.yoff2 = cd->yoff2;
		offset.xadvance = cd->xadvance;

		_texture_offsets.write[i] = offset;
	}

	memdelete_arr(cdata);

	_initialized = true;

#undef MERGE_TABLE
#undef MERGE_PACKED_TABLE
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

Vector2 Font::generate_mesh(const String &p_text, Ref<Mesh> &p_into, const Color &p_color) {
	ERR_FAIL_COND_V(!_initialized, Vector2());
	ERR_FAIL_COND_V(!p_into.is_valid(), Vector2());

	float X = 0;
	float Y = _linedist * _factor * _scale;
	float W = 0;
	float L = _ascent * _factor * _scale;
	float LL = L; // LL=largest linedist

	int mesh_index_offset = p_into->indices.size();

	// parse string
	for (int i = 0, end = p_text.length(); i < end; ++i) {
		uint32_t ch = p_text[i];

		if (ch == '\n') {
			// change cursor, advance y, record largest x as width, increase height
			if (X > W) {
				W = X;
			}

			X = 0.0;
			Y += _linedist * _factor * _scale;

			continue;
		}

		int cp = ch - _begin;

		const TextureOffset &t = _texture_offsets[_cp2iter[cp]];

		p_into->add_uv(t.x0, t.y0);
		p_into->add_color(p_color);
		p_into->add_vertex2(X + t.xoff, Y + t.yoff);

		p_into->add_uv(t.x1, t.y1);
		p_into->add_color(p_color);
		p_into->add_vertex2(X + t.xoff2, Y + t.yoff2);

		p_into->add_uv(t.x0, t.y1);
		p_into->add_color(p_color);
		p_into->add_vertex2(X + t.xoff, Y + t.yoff2);

		p_into->add_uv(t.x1, t.y0);
		p_into->add_color(p_color);
		p_into->add_vertex2(X + t.xoff2, Y + t.yoff);

		p_into->add_triangle(mesh_index_offset + 1, mesh_index_offset + 0, mesh_index_offset + 2);
		p_into->add_triangle(mesh_index_offset + 0, mesh_index_offset + 1, mesh_index_offset + 3);

		mesh_index_offset += 4;

		X += t.xadvance * _scale;
	}

	Y += (-_descent + _linegap) * _factor * _scale;

	return Vector2(W * W > X * X ? W : X, Y * Y > LL * LL ? Y : LL).abs();
}

// Calculate the size of a string, in the pixel size specified. Count stray newlines too.
Vector2 Font::get_string_size(const String &p_text) {
	ERR_FAIL_COND_V(!_initialized, Vector2());

	float X = 0;
	float Y = _linedist * _factor * _scale;
	float W = 0;
	float L = _ascent * _factor * _scale;
	float LL = L; // LL=largest linedist

	// parse string
	for (int i = 0, end = p_text.length(); i < end; ++i) {
		uint32_t ch = p_text[i];

		if (ch == '\n') {
			// change cursor, advance y, record largest x as width, increase height
			if (X > W) {
				W = X;
			}

			X = 0.0;
			Y += _linedist * _factor * _scale;

			continue;
		}

		int cp = ch - _begin;
		const TextureOffset &t = _texture_offsets[_cp2iter[cp]];
		X += t.xadvance * _scale;
	}

	Y += (-_descent + _linegap) * _factor * _scale;

	return Vector2(W * W > X * X ? W : X, Y * Y > LL * LL ? Y : LL).abs();
}

Font::FontMetrics Font::font_metrics() {
	FontMetrics m;

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

void Font::unload() {
	if (!_initialized) {
		return;
	}

	_num_glyphs = 0;
	_cp2iter = NULL;
	_iter2cp = NULL;
	_begin = 0;

	_initialized = false;

	_height = 0;
	_width = 0;
	_font_size = 0;
	_factor = 0;
	_scale = 0;

	_ascent = 0;
	_descent = 0;
	_linegap = 0;
	_linedist = 0;

	_image.unref();
	_texture.unref();

	_texture_offsets.clear();
}

Font::Font() {
	_num_glyphs = 0;
	_cp2iter = NULL;
	_iter2cp = NULL;
	_begin = 0;

	_initialized = false;

	_height = 0;
	_width = 0;
	_font_size = 0;
	_factor = 0;
	_scale = 0;

	_ascent = 0;
	_descent = 0;
	_linegap = 0;
	_linedist = 0;
}

Font::~Font() {
	unload();
}
