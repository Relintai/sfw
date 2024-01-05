#ifndef RENDERER_H
#define RENDERER_H

//--STRIP
#include "core/color.h"
#include "core/rect2.h"
#include "core/transform.h"
#include "core/transform_2d.h"
#include "core/vector2i.h"

#include "object/object.h"
#include "object/reference.h"
//--STRIP

class Mesh;
class Material;
class Texture;
class Font;
class FontMaterial;
class TextureMaterial2D;
class ColorMaterial2D;

class Renderer : public Object {
	SFW_OBJECT(Renderer, Object);

public:
	bool get_depth_buffer_enable() const;
	void set_depth_buffer_enable(const bool p_depth_buffer);

	void draw_point(const Vector2 &p_position, const Color &p_color = Color(1, 1, 1));
	void draw_line(const Vector2 &p_from, const Vector2 &p_to, const Color &p_color = Color(1, 1, 1), const real_t p_width = 1);
	void draw_line_rect(const Rect2 &p_rect, const Color &p_color = Color(1, 1, 1), const real_t p_width = 1);
	void draw_rect(const Rect2 &p_rect, const Color &p_color = Color(1, 1, 1));

	void draw_texture(const Ref<Texture> &p_texture, const Rect2 &p_dst_rect, const Color &p_modulate = Color(1, 1, 1));
	void draw_texture_clipped(const Ref<Texture> &p_texture, const Rect2 &p_src_rect, const Rect2 &p_dst_rect, const Color &p_modulate = Color(1, 1, 1));
	void draw_texture_tr(const Transform2D &p_transform_2d, const Ref<Texture> &p_texture, const Rect2 &p_dst_rect, const Color &p_modulate = Color(1, 1, 1));
	void draw_texture_clipped_tr(const Transform2D &p_transform_2d, const Ref<Texture> &p_texture, const Rect2 &p_src_rect, const Rect2 &p_dst_rect, const Color &p_modulate = Color(1, 1, 1));

	void draw_mesh_2d(const Ref<Mesh> &p_mesh, const Ref<Texture> &p_texture, const Vector2 &p_position);
	void draw_mesh_2d_tr(const Ref<Mesh> &p_mesh, const Ref<Texture> &p_texture, const Transform2D &p_transform_2d);
	void draw_mesh_2d_mat(const Ref<Mesh> &p_mesh, const Ref<Material> &p_material, const Vector2 &p_position);
	void draw_mesh_2d_mat_tr(const Ref<Mesh> &p_mesh, const Ref<Material> &p_material, const Transform2D &p_transform_2d);

	void draw_text_2d(const String &p_text, const Ref<Font> &p_font, const Vector2 &p_position, const Color &p_color = Color(1, 1, 1));
	void draw_text_2d_tf(const String &p_text, const Ref<Font> &p_font, const Transform2D &p_transform_2d, const Color &p_color = Color(1, 1, 1));
	void draw_text_2d_tf_material(const String &p_text, const Ref<Font> &p_font, const Ref<Material> &p_material, const Transform2D &p_transform_2d, const Color &p_color = Color(1, 1, 1));

	//add draw colored, draw textured, also with and without transform -> p_transform give default arg
	void draw_mesh_3d(const Ref<Mesh> &p_mesh, const Ref<Material> &p_material, const Transform &p_transform);

	//TODO
	//camera set transform
	//3d cam matrix stack
	//3d cam proj setup
	//reset -> rename camera_2d_projection_setup(), push etc
	//3d proj setup
	//3d camera matrix stack

	Transform2D camera_2d_get_current_model_view_matrix() const;
	void camera_2d_push_model_view_matrix(const Transform2D &p_transform_2d);
	void camera_2d_pop_model_view_matrix();
	int get_camera_2d_model_view_matrix_stack_size() const;
	void camera_2d_reset();

	void camera_3d_reset();

	void clear_screen(const Color &p_color);

	Vector2i get_window_size() const;
	float get_window_aspect() const;

	static void initialize();
	static void destroy();

	Renderer();
	~Renderer();

	static Renderer *get_singleton();

private:
	static Renderer *_singleton;

	bool _depth_buffer;

	Ref<Mesh> _2d_mesh;
	Ref<Mesh> _3d_mesh;
	Ref<Mesh> _font_mesh;

	Ref<TextureMaterial2D> _texture_material_2d;
	Ref<FontMaterial> _font_material;
	Ref<ColorMaterial2D> _color_material_2d;

	Vector<Transform2D> camera_2d_model_view_matrix_stack;
};

#endif