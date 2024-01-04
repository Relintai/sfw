#ifndef FONT_MATERIAL_H
#define FONT_MATERIAL_H

#include "render_core/material.h"

#include "core/color.h"

#include "render_core/render_state.h"

class FontMaterial : public Material {
public:
	int get_material_id() {
		return 10;
	}

	void bind_uniforms() {
		set_uniform(projection_matrix_location, RenderState::projection_matrix_3d);
		set_uniform(model_view_matrix_location, RenderState::model_view_matrix_3d);

		glUniform4f(tri_color_uniform_location, color.r, color.g, color.b, color.a);
	}

	void setup_uniforms() {
		projection_matrix_location = get_uniform("u_proj_matrix");
		model_view_matrix_location = get_uniform("u_model_view_matrix");

		tri_color_uniform_location = get_uniform("fragment_color");
	}

	GLuint get_program() {
		return shader->program;
	}

	const GLchar **get_vertex_shader_source() {
		static const GLchar *vertex_shader_source[] = {
			"\
			\n\
			in Vector2 vertexPosition;\n\
			in vec4 instanceGlyph;\n\
			\n\
			uniform sampler2D sampler_font;\n\
			uniform sampler2D sampler_meta;\n\
			\n\
			uniform float offset_firstline; // ascent - descent - linegap/2\n\
			uniform float scale_factor;     // scaling factor proportional to font size\n\
			uniform Vector2 string_offset;     // offset of upper-left corner\n\
			\n\
			uniform Vector2 res_meta;   // 96x2 \n\
			uniform Vector2 res_bitmap; // 512x256\n\
			uniform Vector2 resolution; // screen resolution\n\
			\n\
			out Vector2 uv;\n\
			out float color_index; // for syntax highlighting\n\
			\n\
			void main() { \
				// (xoff, yoff, xoff2, yoff2), from second row of texture\n\
				vec4 q2 = texture(sampler_meta, Vector2((instanceGlyph.z + 0.5)/res_meta.x, 0.75))*vec4(res_bitmap, res_bitmap);\n\
			\n\
				Vector2 p = vertexPosition*(q2.zw - q2.xy) + q2.xy; // offset and scale it properly relative to baseline\n\
				p *= Vector2(1.0, -1.0);                            // flip y, since texture is upside-down\n\
				p.y -= offset_firstline;                         // make sure the upper-left corner of the string is in the upper-left corner of the screen\n\
				p *= scale_factor;                               // scale relative to font size\n\
				p += instanceGlyph.xy + string_offset;           // move glyph into the right position\n\
				p *= 2.0/resolution;                             // to NDC\n\
				p += Vector2(-1.0, 1.0);                            // move to upper-left corner instead of center\n\
			\n\
				gl_Position = vec4(p, 0.0, 1.0);\n\
			\n\
				// (x0, y0, x1-x0, y1-y0), from first row of texture\n\
				vec4 q = texture(sampler_meta, Vector2((instanceGlyph.z + 0.5)/res_meta.x, 0.25));\n\
			\n\
				// send the correct uv's in the font atlas to the fragment shader\n\
				uv = q.xy + vertexPosition*q.zw;\n\
				color_index = instanceGlyph.w;\n\
			}\n"
		};

		return vertex_shader_source;
	}

	const GLchar **
	get_fragment_shader_source() {
		static const GLchar *fragment_shader_source[] = {
			"\
			\n\
			in Vector2 uv;\n\
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
			}\n"
		};

		return fragment_shader_source;
	}

	FontMaterial() {
	}

	GLint projection_matrix_location;
	GLint model_view_matrix_location;

	GLint tri_color_uniform_location;
	Color color;
};

#endif // TEXT_MATERIAL_H
