#ifndef CAMERA_H
#define CAMERA_H

#include "3rd_glad.h"

#include "projection.h"
#include "transform.h"
#include "vector3.h"

class Camera {
public:
	virtual void bind();

	void make_current();

	Camera();
	virtual ~Camera();

	float size;
    float screen_aspect_ratio; //p_viewport_size.width / (float)p_viewport_size.height,
	float znear;
	float zfar;
    bool vaspect;

	static Camera *current_camera;

	Transform camera_transform;
	Transform model_view_matrix;
	Projection projection_matrix;
};

class OrthographicCamera : public Camera {
public:
	void bind();

	OrthographicCamera();
	~OrthographicCamera();
};

class PerspectiveCamera : public Camera {
public:
	float fov;

	void bind();

	PerspectiveCamera();
	~PerspectiveCamera();
};

//frustum

#endif // CAMERA_H
