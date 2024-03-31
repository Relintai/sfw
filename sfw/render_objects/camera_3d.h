//--STRIP
#ifndef CAMERA_3D_H
#define CAMERA_3D_H
//--STRIP

//--STRIP
#include "render_core/3rd_glad.h"

#include "render_objects/object_3d.h"

#include "core/projection.h"
#include "core/transform.h"
#include "core/vector3.h"
//--STRIP

class Camera3D : public Object3D {
	SFW_OBJECT(Camera3D, Object3D);

public:
	Transform get_camera_transform();
	void set_camera_transform(const Transform &p_value);

	Transform get_model_view_matrix();
	void set_model_view_matrix(const Transform &p_value);

	Projection get_projection_matrix();
	void set_projection_matrix(const Projection &p_value);

	virtual void bind();

	void make_current();
	
	// From Pandemonium
	virtual Vector3 project_ray_normal(const Point2 &p_pos) const;
	virtual Vector3 project_ray_origin(const Point2 &p_pos) const;
	virtual Vector3 project_local_ray_normal(const Point2 &p_pos) const;
	virtual Point2 unproject_position(const Vector3 &p_pos) const;
	bool is_position_behind(const Vector3 &p_pos) const;
	virtual Vector3 project_position(const Point2 &p_point, float p_z_depth) const;

	virtual Vector<Vector3> get_near_plane_points() const;

	Camera3D();
	virtual ~Camera3D();

	float size;
	float screen_aspect_ratio; //p_viewport_size.width / (float)p_viewport_size.height,
	float znear;
	float zfar;
	bool vaspect;

	static Camera3D *current_camera;

protected:
	Transform _camera_transform;
	Transform _model_view_matrix;
	Projection _projection_matrix;
};

class OrthographicCamera : public Camera3D {
public:
	void bind();
	
	virtual Vector3 project_local_ray_normal(const Point2 &p_pos) const;
	virtual Point2 unproject_position(const Vector3 &p_pos) const;
	virtual Vector3 project_position(const Point2 &p_point, float p_z_depth) const;
	
	virtual Vector<Vector3> get_near_plane_points() const;

	OrthographicCamera();
	~OrthographicCamera();
};

class PerspectiveCamera : public Camera3D {
public:
	float fov;

	void bind();
	
	virtual Vector3 project_local_ray_normal(const Point2 &p_pos) const;
	virtual Vector3 project_ray_origin(const Point2 &p_pos) const;
	virtual Point2 unproject_position(const Vector3 &p_pos) const;
	virtual Vector3 project_position(const Point2 &p_point, float p_z_depth) const;
	
	virtual Vector<Vector3> get_near_plane_points() const;

	PerspectiveCamera();
	~PerspectiveCamera();
};

class FrustumCamera : public Camera3D {
public:
	float offset;

	void bind();

	FrustumCamera();
	~FrustumCamera();
};

//--STRIP
#endif // CAMERA_H
//--STRIP
