//--STRIP
#ifndef RENDERER_H
#define RENDERER_H
//--STRIP

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
class TextureMaterial;
class ColorMaterial;
class ColoredMaterial;

class Renderer : public Object {
	SFW_OBJECT(Renderer, Object);

public:
	bool get_depth_buffer_enable() const;
	void set_depth_buffer_enable(const bool p_depth_buffer);

	enum FaceCulling {
		FACE_CULLING_OFF = 0,
		FACE_CULLING_FRONT,
		FACE_CULLING_BACK,
		FACE_CULLING_FRONT_AND_BACK,
	};

	FaceCulling get_face_culling() const;
	void set_face_culling(const FaceCulling p_face_culling);

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

	void draw_mesh_3d(const Ref<Mesh> &p_mesh, const Ref<Material> &p_material, const Transform &p_transform = Transform());
	void draw_mesh_3d_colored(const Ref<Mesh> &p_mesh, const Color &p_color, const Transform &p_transform = Transform());
	void draw_mesh_3d_vertex_colored(const Ref<Mesh> &p_mesh, const Transform &p_transform = Transform());
	void draw_mesh_3d_textured(const Ref<Mesh> &p_mesh, const Ref<Texture> &p_texture, const Transform &p_transform = Transform());

	//2D Camera API

	void camera_2d_bind();

	Transform camera_2d_get_current_projection_matrix() const;
	void camera_2d_push_projection_matrix(const Transform &p_transform);
	void camera_2d_pop_projection_matrix();
	int get_camera_2d_projection_matrix_stack_size() const;

	Transform2D camera_2d_get_current_model_view_matrix() const;
	void camera_2d_push_model_view_matrix(const Transform2D &p_transform_2d);
	void camera_2d_pop_model_view_matrix();
	int get_camera_2d_model_view_matrix_stack_size() const;

	void camera_2d_projection_set_to_window();
	void camera_2d_projection_set_to_size(const Size2i &p_size);

	//3D Camera API

	void camera_3d_bind();

	Transform camera_3d_get_current_camera_transform_matrix() const;
	void camera_3d_push_camera_transform_matrix(const Transform &p_transform);
	void camera_3d_pop_camera_transform_matrix();
	int get_camera_3d_camera_transform_matrix_stack_size() const;

	Transform camera_3d_get_current_model_view_matrix() const;
	void camera_3d_push_model_view_matrix(const Transform &p_transform);
	void camera_3d_pop_model_view_matrix();
	int get_camera_3d_model_view_matrix_stack_size() const;

	// Aspect Ratio = w / h
	void camera_3d_projection_set_to_orthographic(float aspect_ratio, float size = 1.0, float znear = 0.05, float zfar = 100, bool vaspect = false);
	void camera_3d_projection_set_to_perspective(float aspect_ratio, float size = 1.0, float znear = 0.05, float zfar = 100, bool vaspect = false, float fov = 70);
	void camera_3d_projection_set_to_frustum(float aspect_ratio, float size = 1.0, float znear = 0.05, float zfar = 100, bool vaspect = false, float offset = 0);

	Projection camera_3d_get_projection_matrix() const;
	void camera_3d_set_projection_matrix(const Projection &p_projection);

	// Other Helpers

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
	FaceCulling _face_culling;

	Ref<Mesh> _2d_mesh;
	Ref<Mesh> _3d_mesh;
	Ref<Mesh> _font_mesh;

	Ref<TextureMaterial2D> _texture_material_2d;
	Ref<FontMaterial> _font_material;
	Ref<ColorMaterial2D> _color_material_2d;

	Transform _camera_2d_projection_matrix;
	Transform2D _camera_2d_model_view_matrix;

	Vector<Transform> _camera_2d_projection_matrix_stack;
	Vector<Transform2D> _camera_2d_model_view_matrix_stack;

	Projection _camera_3d_projection;
	Transform _camera_3d_camera_transform_matrix;
	Transform _camera_3d_model_view_matrix;

	Vector<Transform> _camera_3d_camera_transform_matrix_stack;
	Vector<Transform> _camera_3d_model_view_matrix_stack;

	Ref<TextureMaterial> _texture_material_3d;
	Ref<ColorMaterial> _color_material_3d;
	Ref<ColoredMaterial> _colored_material_3d;
};

//--STRIP
#endif
//--STRIP
