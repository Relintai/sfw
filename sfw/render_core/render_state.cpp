//--STRIP
#include "render_core/render_state.h"
#include "render_core/frame_buffer.h"
//--STRIP

Transform RenderState::camera_transform_3d;
Transform RenderState::model_view_matrix_3d;
Projection RenderState::projection_matrix_3d;

Transform2D RenderState::model_view_matrix_2d;
Transform RenderState::projection_matrix_2d;

Rect2i RenderState::render_rect;

Ref<FrameBuffer> RenderState::current_framebuffer;

void RenderState::apply_render_rect() {
	glViewport(render_rect.position.x, render_rect.position.y, render_rect.size.x, render_rect.size.y);
}

void RenderState::window_update_render_rect_size(const int p_width, const int p_height) {
	if (current_framebuffer.is_valid()) {
		return;
	}
	
	render_rect = Rect2i(0, 0, p_width, p_height);
}

RenderState::RenderState() {
}
RenderState::~RenderState() {
}
