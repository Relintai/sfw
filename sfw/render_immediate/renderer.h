#ifndef RENDERER_H
#define RENDERER_H

#include "core/color.h"
#include "core/rect2.h"
#include "sprite.h"
#include "texture.h"

#include <SDL.h>

class Renderer {
public:
	void present();
	void set_draw_color(const Uint8 r, const Uint8 g, const Uint8 b, const Uint8 a);
	void set_draw_color(const Color &color);
	void clear();

	SDL_BlendMode get_blend_mode() const;
	void set_blend_mode(const SDL_BlendMode mode);

	void draw_point(const int x, const int y);
	void draw_point(const float x, const float y);

	void draw_line(const int x1, const int x2, const int y1, const int y2);
	void draw_line(const float x1, const float x2, const float y1, const float y2);

	void draw_rect(const Rect2 &rect);

	void draw_fill_rect(const Rect2 &rect);

	void draw_texture(const Texture &texture, const Rect2 &dst_rect);
	void draw_texture(const Texture &texture, const Rect2 &src_rect, const Rect2 &dst_rect);
	void draw_texture(const Texture &texture, const Rect2 &src_rect, const Rect2 &dst_rect, const double angle, const float cx = 0, const float cy = 0, const SDL_RendererFlip flip = SDL_FLIP_NONE);

	void draw_sprite(const Sprite &sprite);
	void draw_sprite(const Sprite *sprite);

	int get_dpi() const;
	int get_window_size_w() const;
	int get_window_size_h() const;
	int get_size_w() const;
	int get_size_h() const;
	void set_size(const int w, const int h) const;
	void get_size(int *w, int *h) const;

	float get_scale_w() const;
	float get_scale_h() const;
	void set_scale(const float w, const float h) const;
	void get_scale(float *w, float *h) const;

	bool get_integer_scaling() const;
	void set_integer_scaling(const bool enable);

	Rect2 get_viewport() const;
	void set_viewport(const Rect2 &rect) const;

	Rect2 get_clip_rect() const;
	void set_clip_rect(Rect2 *rect) const;
	bool clip_rect_enabled() const;

	bool render_target_supported();

	SDL_Texture *get_render_target();
	void set_render_target(Texture *texture);

	void initialize();
	void destroy();

	SDL_Window *get_window();
	SDL_Renderer *get_renderer();

	Renderer();
	Renderer(unsigned int flags, unsigned int window_flags, int window_width = 640, int window_height = 480);
	virtual ~Renderer();

	static Renderer *get_singleton();

private:
	int _initial_window_width;
	int _initial_window_height;

	unsigned int _flags;
	unsigned int _window_flags;

	SDL_Window *_window;
	SDL_Renderer *_renderer;

	int _window_display_index;

	static Renderer *_singleton;
};

#endif