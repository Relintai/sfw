#ifndef RENDER_STATE_H
#define RENDER_STATE_H

#include "core/projection.h"
#include "core/transform.h"
#include "core/vector3.h"
#include "core/transform_2d.h"
#include "core/vector2.h"

class RenderState {
public:
	static Transform camera_transform_3d;
	static Transform model_view_matrix_3d;
	static Projection projection_matrix_3d;

	static Transform2D model_view_matrix_2d;
	static Transform projection_matrix_2d;

    //TODO should probably add the current shader here, and active material etc.
};


#endif // RENDER_STATE_H
