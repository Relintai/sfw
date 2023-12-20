#ifndef CAMERA_2D_H
#define CAMERA_2D_H

#include "3rd_glad.h"

#include "object_2d.h"

#include "transform.h"
#include "transform_2d.h"
#include "vector2.h"

class Camera2D : Object2D {
public:
	virtual void bind();

	void make_current();

	//void push_transform(const Transform2D &transform);
	//void pop_transform();

	Camera2D();
	virtual ~Camera2D();

	Vector2 size;

	//RenderTexture target ?
	//bool auto_set_size?
	//func auto_set_size()?

	static Camera2D *current_camera;

	Transform2D model_view_matrix;
	Transform projection_matrix;
};

#endif // CAMERA_H
