#ifndef RENDERER_H
#define RENDERER_H

#include "core/color.h"
#include "core/rect2.h"
#include "core/transform.h"
#include "core/transform_2d.h"
#include "core/rect2.h"
#include "core/vector2i.h"

#include "object/object.h"
#include "object/reference.h"

class Mesh;
class Material;
class Texture;
class Font;
class FontMaterial;
class TextureMaterial2D;

class Renderer : public Object {
	SFW_OBJECT(Renderer, Object);

public:
	void draw_point(const Vector2 &p_position, const Color &p_color = Color(1, 1, 1));
	void draw_line(const Vector2 &p_from, const Vector2 &p_to, const Color &p_color = Color(1, 1, 1), const real_t p_width = 1);
	void draw_line_rect(const Rect2 &p_rect, const Color &p_color = Color(1, 1, 1));
	void draw_rect(const Rect2 &p_rect, const Color &p_color = Color(1, 1, 1));

	void draw_texture(const Ref<Texture> &p_texture, const Rect2 &dst_rect, const Color &p_modulate = Color(1, 1, 1));
	void draw_texture_clipped(const Ref<Texture> &p_texture, const Rect2 &p_src_rect, const Rect2 &p_dst_rect, const Color &p_modulate = Color(1, 1, 1));

	void draw_mesh_2d(const Ref<Mesh> &p_mesh, const Ref<Material> &p_material, const Transform2D &p_transform_2d);
	void draw_mesh_3d(const Ref<Mesh> &p_mesh, const Ref<Material> &p_material, const Transform &p_transform);

	void draw_text_2d(const Ref<Font> &p_mesh, const Vector2 &p_position, const Color &p_color = Color(1, 1, 1));
	void draw_text_2d_tf(const Ref<Font> &p_mesh, const Transform2D &p_transform_2d, const Color &p_color = Color(1, 1, 1));
	void draw_text_2d_tf_material(const Ref<Font> &p_mesh, const Ref<Material> &p_material, const Transform2D &p_transform_2d);

	Vector2i get_window_size() const;
	float get_window_aspect() const;

	static void initialize();
	static void destroy();

	Renderer();
	~Renderer();

	static Renderer *get_singleton();

private:
	static Renderer *_singleton;

	Ref<Mesh> _2d_mesh;
	Ref<Mesh> _3d_mesh;

	Ref<TextureMaterial2D> _texture_material_2d;
	Ref<FontMaterial> _font_material;
};

#endif