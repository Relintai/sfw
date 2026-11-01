//--STRIP
#ifndef RENDER_STATE_H
#define RENDER_STATE_H
//--STRIP

//--STRIP
#include "core/projection.h"
#include "core/rect2i.h"
#include "core/transform.h"
#include "core/transform_2d.h"
#include "core/vector2.h"
#include "core/vector3.h"
#include "object/reference.h"
//--STRIP

class FrameBuffer;

class RenderState {
public:
	static Transform camera_transform_3d;
	static Transform model_view_matrix_3d;
	static Projection projection_matrix_3d;

	static Transform2D model_view_matrix_2d;
	static Transform projection_matrix_2d;

	static Rect2i render_rect;
	static Ref<FrameBuffer> current_framebuffer;

	//TODO should probably add the current shader here, and active material etc.
	
	static void apply_render_rect();
	
	static void window_update_render_rect_size(const int p_width, const int p_height);

	RenderState();
	~RenderState();
};

//--STRIP
#endif // RENDER_STATE_H
//--STRIP
