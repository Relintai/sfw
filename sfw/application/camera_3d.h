#ifndef CAMERA_3D_H
#define CAMERA_3D_H

#include "3rd_glad.h"

#include "projection.h"
#include "transform.h"
#include "vector3.h"

class Camera3D {
public:
	virtual void bind();

	void make_current();

	Camera3D();
	virtual ~Camera3D();

	float size;
    float screen_aspect_ratio; //p_viewport_size.width / (float)p_viewport_size.height,
	float znear;
	float zfar;
    bool vaspect;

	static Camera3D *current_camera;

	Transform camera_transform;
	Transform model_view_matrix;
	Projection projection_matrix;
};

class OrthographicCamera : public Camera3D {
public:
	void bind();

	OrthographicCamera();
	~OrthographicCamera();
};

class PerspectiveCamera : public Camera3D {
public:
	float fov;

	void bind();

	PerspectiveCamera();
	~PerspectiveCamera();
};

class FrustumCamera : public Camera3D {
public:
	//todo
	void bind();

	FrustumCamera();
	~FrustumCamera();
};


#endif // CAMERA_H
