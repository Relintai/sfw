//--STRIP
#ifndef CAMERA_2D_H
#define CAMERA_2D_H
//--STRIP

//--STRIP
#include "render_core/3rd_glad.h"

#include "render_objects/object_2d.h"

#include "core/transform.h"
#include "core/transform_2d.h"
#include "core/vector2.h"
//--STRIP

class Camera2D : public Object2D {
	SFW_OBJECT(Camera2D, Object2D);

public:
	Transform2D get_model_view_matrix();
	void set_model_view_matrix(const Transform2D &p_value);

	Transform get_projection_matrix();
	void set_projection_matrix(const Transform &p_value);

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

protected:
	Transform2D _model_view_matrix;
	Transform _projection_matrix;
};

//--STRIP
#endif // CAMERA_H
//--STRIP
