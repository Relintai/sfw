//--STRIP
#include "render_objects/camera_3d.h"

#include "core/math_funcs.h"

#include "render_core/render_state.h"
//--STRIP

Transform Camera3D::get_camera_transform() {
	return _camera_transform;
}
void Camera3D::set_camera_transform(const Transform &p_value) {
	_camera_transform = p_value;

	if (current_camera == this) {
		RenderState::camera_transform_3d = _camera_transform;
	}
}

Transform Camera3D::get_model_view_matrix() {
	return _model_view_matrix;
}
void Camera3D::set_model_view_matrix(const Transform &p_value) {
	_model_view_matrix = p_value;

	if (current_camera == this) {
		RenderState::model_view_matrix_3d = _model_view_matrix;
	}
}

Projection Camera3D::get_projection_matrix() {
	return _projection_matrix;
}
void Camera3D::set_projection_matrix(const Projection &p_value) {
	_projection_matrix = p_value;

	if (current_camera == this) {
		RenderState::projection_matrix_3d = _projection_matrix;
	}
}

void Camera3D::bind() {
	make_current();

	_model_view_matrix = Transform();

	RenderState::camera_transform_3d = _camera_transform;
	RenderState::model_view_matrix_3d = _model_view_matrix;
	RenderState::projection_matrix_3d = _projection_matrix;
}

void Camera3D::make_current() {
	current_camera = this;
}

Vector3 Camera3D::project_ray_normal(const Point2 &p_pos) const {
	Vector3 ray = project_local_ray_normal(p_pos);
	return transform.basis.xform(ray).normalized();
};

Vector3 Camera3D::project_local_ray_normal(const Point2 &p_pos) const {
	Size2 viewport_size = RenderState::render_rect.size;
	Vector2 cpos = p_pos;
	Vector3 ray;

	Projection cm;
	cm.set_perspective(70, viewport_size.aspect(), znear, zfar, true);
	Vector2 screen_he = cm.get_viewport_half_extents();
	ray = Vector3(((cpos.x / viewport_size.width) * 2.0 - 1.0) * screen_he.x, ((1.0 - (cpos.y / viewport_size.height)) * 2.0 - 1.0) * screen_he.y, -znear).normalized();

	return ray;
};

Vector3 Camera3D::project_ray_origin(const Point2 &p_pos) const {
	Size2 viewport_size = RenderState::render_rect.size;
	Vector2 cpos = p_pos;
	ERR_FAIL_COND_V(viewport_size.y == 0, Vector3());

	Vector2 pos = cpos / viewport_size;
	float vsize, hsize;

	vsize = size / viewport_size.aspect();
	hsize = size;

	Vector3 ray;
	ray.x = pos.x * (hsize)-hsize / 2;
	ray.y = (1.0 - pos.y) * (vsize)-vsize / 2;
	ray.z = -znear;
	ray = transform.xform(ray);
	return ray;
};

bool Camera3D::is_position_behind(const Vector3 &p_pos) const {
	Transform t = transform;
	Vector3 eyedir = -t.basis.get_axis(2).normalized();
	return eyedir.dot(p_pos - t.origin) < znear;
}

Vector<Vector3> Camera3D::get_near_plane_points() const {
	Size2 viewport_size = RenderState::render_rect.size;

	Projection cm;

	cm.set_perspective(70, viewport_size.aspect(), znear, zfar, true);

	Vector3 endpoints[8];
	cm.get_endpoints(Transform(), endpoints);

	Vector<Vector3> points;
	points.push_back(Vector3());
	for (int i = 0; i < 4; i++) {
		points.push_back(endpoints[i + 4]);
	}
	return points;
}

Point2 Camera3D::unproject_position(const Vector3 &p_pos) const {
	Size2 viewport_size = RenderState::render_rect.size;

	Projection cm;

	cm.set_perspective(70, viewport_size.aspect(), znear, zfar, true);

	Plane p(transform.xform_inv(p_pos), 1.0);

	p = cm.xform(p);
	p.normal /= p.d;

	Point2 res;
	res.x = (p.normal.x * 0.5 + 0.5) * viewport_size.x;
	res.y = (-p.normal.y * 0.5 + 0.5) * viewport_size.y;

	return res;
}

Vector3 Camera3D::project_position(const Point2 &p_point, float p_z_depth) const {
	if (p_z_depth == 0) {
		return transform.origin;
	}
	
	Size2 viewport_size = RenderState::render_rect.size;

	Projection cm;

	cm.set_perspective(70, viewport_size.aspect(), p_z_depth, zfar, true);

	Vector2 vp_he = cm.get_viewport_half_extents();

	Vector2 point;
	point.x = (p_point.x / viewport_size.x) * 2.0 - 1.0;
	point.y = (1.0 - (p_point.y / viewport_size.y)) * 2.0 - 1.0;
	point *= vp_he;

	Vector3 p(point.x, point.y, -p_z_depth);

	return transform.xform(p);
}


Camera3D::Camera3D() {
	screen_aspect_ratio = 1; //p_viewport_size.width / (float)p_viewport_size.height,

	znear = 0.05;
	zfar = 100;
	size = 1.0;

	vaspect = false;
}
Camera3D::~Camera3D() {
}

Camera3D *Camera3D::current_camera = NULL;

void OrthographicCamera::bind() {
	_projection_matrix.set_orthogonal(
			size,
			screen_aspect_ratio,
			znear,
			zfar,
			vaspect);

	Camera3D::bind();
}

Vector3 OrthographicCamera::project_local_ray_normal(const Point2 &p_pos) const {
	return Vector3(0, 0, -1);
};


Point2 OrthographicCamera::unproject_position(const Vector3 &p_pos) const {
	Size2 viewport_size = RenderState::render_rect.size;

	Projection cm;

	cm.set_orthogonal(size, viewport_size.aspect(), znear, zfar, true);

	Plane p(transform.xform_inv(p_pos), 1.0);

	p = cm.xform(p);
	p.normal /= p.d;

	Point2 res;
	res.x = (p.normal.x * 0.5 + 0.5) * viewport_size.x;
	res.y = (-p.normal.y * 0.5 + 0.5) * viewport_size.y;

	return res;
}

Vector3 OrthographicCamera::project_position(const Point2 &p_point, float p_z_depth) const {
	Size2 viewport_size = RenderState::render_rect.size;

	Projection cm;

	cm.set_orthogonal(size, viewport_size.aspect(), p_z_depth, zfar, true);

	Vector2 vp_he = cm.get_viewport_half_extents();

	Vector2 point;
	point.x = (p_point.x / viewport_size.x) * 2.0 - 1.0;
	point.y = (1.0 - (p_point.y / viewport_size.y)) * 2.0 - 1.0;
	point *= vp_he;

	Vector3 p(point.x, point.y, -p_z_depth);

	return transform.xform(p);
}


Vector<Vector3> OrthographicCamera::get_near_plane_points() const {
	Size2 viewport_size = RenderState::render_rect.size;

	Projection cm;

	cm.set_orthogonal(size, viewport_size.aspect(), znear, zfar, true);

	Vector3 endpoints[8];
	cm.get_endpoints(Transform(), endpoints);

	Vector<Vector3> points;
	points.push_back(Vector3());
	for (int i = 0; i < 4; i++) {
		points.push_back(endpoints[i + 4]);
	}
	return points;
}

OrthographicCamera::OrthographicCamera() :
		Camera3D() {
}
OrthographicCamera::~OrthographicCamera() {
}

void PerspectiveCamera::bind() {
	_projection_matrix.set_perspective(
			fov,
			screen_aspect_ratio,
			znear,
			zfar,
			vaspect);

	Camera3D::bind();
}

Vector3 PerspectiveCamera::project_local_ray_normal(const Point2 &p_pos) const {
	Size2 viewport_size = RenderState::render_rect.size;
	Vector2 cpos = p_pos;
	Vector3 ray;

	Projection cm;
	cm.set_perspective(fov, viewport_size.aspect(), znear, zfar, false);
	Vector2 screen_he = cm.get_viewport_half_extents();
	ray = Vector3(((cpos.x / viewport_size.width) * 2.0 - 1.0) * screen_he.x, ((1.0 - (cpos.y / viewport_size.height)) * 2.0 - 1.0) * screen_he.y, -znear).normalized();

	return ray;
};

Vector3 PerspectiveCamera::project_ray_origin(const Point2 &p_pos) const {
	return transform.origin;
};


Point2 PerspectiveCamera::unproject_position(const Vector3 &p_pos) const {
	Size2 viewport_size = RenderState::render_rect.size;

	Projection cm;

	cm.set_perspective(fov, viewport_size.aspect(), znear, zfar, true);
	Plane p(transform.xform_inv(p_pos), 1.0);

	p = cm.xform(p);
	p.normal /= p.d;

	Point2 res;
	res.x = (p.normal.x * 0.5 + 0.5) * viewport_size.x;
	res.y = (-p.normal.y * 0.5 + 0.5) * viewport_size.y;

	return res;
}

Vector3 PerspectiveCamera::project_position(const Point2 &p_point, float p_z_depth) const {
	if (p_z_depth == 0) {
		return transform.origin;
	}
	
	Size2 viewport_size = RenderState::render_rect.size;

	Projection cm;

	cm.set_perspective(fov, viewport_size.aspect(), p_z_depth, zfar, true);

	Vector2 vp_he = cm.get_viewport_half_extents();

	Vector2 point;
	point.x = (p_point.x / viewport_size.x) * 2.0 - 1.0;
	point.y = (1.0 - (p_point.y / viewport_size.y)) * 2.0 - 1.0;
	point *= vp_he;

	Vector3 p(point.x, point.y, -p_z_depth);

	return transform.xform(p);
}


Vector<Vector3> PerspectiveCamera::get_near_plane_points() const {
	Size2 viewport_size = RenderState::render_rect.size;

	Projection cm;

	cm.set_perspective(fov, viewport_size.aspect(), znear, zfar, true);

	Vector3 endpoints[8];
	cm.get_endpoints(Transform(), endpoints);

	Vector<Vector3> points;
	points.push_back(Vector3());
	for (int i = 0; i < 4; i++) {
		points.push_back(endpoints[i + 4]);
	}
	return points;
}


PerspectiveCamera::PerspectiveCamera() :
		Camera3D() {
	fov = 70;
}

PerspectiveCamera::~PerspectiveCamera() {
}

void FrustumCamera::bind() {
	_projection_matrix.set_frustum(
			size,
			screen_aspect_ratio,
			offset,
			znear,
			zfar,
			vaspect);

	Camera3D::bind();
}

FrustumCamera::FrustumCamera() :
		Camera3D() {
	offset = 0;

	_projection_matrix.set_frustum(
			size,
			screen_aspect_ratio,
			offset,
			znear,
			zfar,
			vaspect);
}

FrustumCamera::~FrustumCamera() {
}
