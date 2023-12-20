#include "renderer.h"

#include <cstdio>

#include "core/math.h"

void Renderer::present() {
	SDL_RenderPresent(_renderer);
}

void Renderer::set_draw_color(const Uint8 r, const Uint8 g, const Uint8 b, const Uint8 a) {
	SDL_SetRenderDrawColor(_renderer, r, g, b, a);
}

void Renderer::set_draw_color(const Color &color) {
	SDL_SetRenderDrawColor(_renderer, color.r, color.g, color.b, color.a);
}

void Renderer::clear() {
	SDL_RenderClear(_renderer);
}

SDL_BlendMode Renderer::get_blend_mode() const {
	SDL_BlendMode mode;
	SDL_GetRenderDrawBlendMode(_renderer, &mode);

	return mode;
}
void Renderer::set_blend_mode(const SDL_BlendMode mode) {
	SDL_SetRenderDrawBlendMode(_renderer, mode);
}

void Renderer::draw_point(const int x, const int y) {
	SDL_RenderDrawPoint(_renderer, x, y);
}
void Renderer::draw_point(const float x, const float y) {
	SDL_RenderDrawPointF(_renderer, x, y);
}

void Renderer::draw_line(const int x1, const int x2, const int y1, const int y2) {
	SDL_RenderDrawLine(_renderer, x1, x2, y1, y2);
}
void Renderer::draw_line(const float x1, const float x2, const float y1, const float y2) {
	SDL_RenderDrawLineF(_renderer, x1, x2, y1, y2);
}

void Renderer::draw_rect(const Rect2 &rect) {
	SDL_Rect r = rect.as_rect();

	SDL_RenderDrawRect(_renderer, &r);
}

void Renderer::draw_fill_rect(const Rect2 &rect) {
	SDL_Rect r = rect.as_rect();

	SDL_RenderFillRect(_renderer, &r);
}

void Renderer::draw_texture(const Texture &texture, const Rect2 &dst_rect) {
	SDL_Rect sr;

	sr.x = 0;
	sr.y = 0;
	sr.w = texture.get_width();
	sr.h = texture.get_height();

	SDL_Rect dr = dst_rect.as_rect();

	SDL_RenderCopy(_renderer, texture.get_texture(), &sr, &dr);
}
void Renderer::draw_texture(const Texture &texture, const Rect2 &src_rect, const Rect2 &dst_rect) {
	SDL_Rect sr = src_rect.as_rect();
	SDL_Rect dr = dst_rect.as_rect();

	SDL_RenderCopy(_renderer, texture.get_texture(), &sr, &dr);
}
void Renderer::draw_texture(const Texture &texture, const Rect2 &src_rect, const Rect2 &dst_rect, const double angle, const float cx, const float cy, const SDL_RendererFlip flip) {
	SDL_Rect sr = src_rect.as_rect();
	SDL_FRect dr = dst_rect.as_frect();

	SDL_FPoint p;

	p.x = cx;
	p.y = cy;

	SDL_RenderCopyExF(_renderer, texture.get_texture(), &sr, &dr, angle, &p, flip);
}

void Renderer::draw_sprite(const Sprite &sprite) {
	Texture *t = sprite.get_texture();

	if (!t) {
		return;
	}

	t->set_color_mod(sprite.get_color_mod());

	double angle = sprite.get_angle();

	if (Math::is_zero_approx(angle)) {
		SDL_Rect sr = sprite.get_texture_clip_rect().as_rect();
		SDL_Rect dr = sprite.get_transform().as_rect();

		SDL_RenderCopy(_renderer, t->get_texture(), &sr, &dr);
	} else {
		SDL_Rect sr = sprite.get_texture_clip_rect().as_rect();
		SDL_FRect dr = sprite.get_transform().as_frect();

		SDL_FPoint p;

		p.x = sprite.get_anchor_x();
		p.y = sprite.get_anchor_y();

		SDL_RenderCopyExF(_renderer, t->get_texture(), &sr, &dr, angle, &p, sprite.get_flip());
	}
}

void Renderer::draw_sprite(const Sprite *sprite) {
	if (!sprite)
		return;

	Texture *t = sprite->get_texture();

	if (!t) {
		return;
	}

	t->set_color_mod(sprite->get_color_mod());

	double angle = sprite->get_angle();

	if (Math::is_zero_approx(angle)) {
		SDL_Rect sr = sprite->get_texture_clip_rect().as_rect();
		SDL_Rect dr = sprite->get_transform().as_rect();

		SDL_RenderCopy(_renderer, t->get_texture(), &sr, &dr);
	} else {
		SDL_Rect sr = sprite->get_texture_clip_rect().as_rect();
		SDL_FRect dr = sprite->get_transform().as_frect();

		SDL_FPoint p;

		p.x = sprite->get_anchor_x();
		p.y = sprite->get_anchor_y();

		SDL_RenderCopyExF(_renderer, t->get_texture(), &sr, &dr, angle, &p, sprite->get_flip());
	}
}

int Renderer::get_dpi() const {
	float ddpi;
	float hdpi;
	float vdpi;

	if (SDL_GetDisplayDPI(_window_display_index, &ddpi, &hdpi, &vdpi)) {
		return ddpi;
	}

	//fallback
	return 1;
}

int Renderer::get_window_size_w() const {
	int w;
	int h;

	SDL_GetWindowSize(_window, &w, &h);

	return w;
}

int Renderer::get_window_size_h() const {
	int w;
	int h;

	SDL_GetWindowSize(_window, &w, &h);

	return h;
}

int Renderer::get_size_w() const {
	int w;
	int h;

	SDL_RenderGetLogicalSize(_renderer, &w, &h);

	return w;
}

int Renderer::get_size_h() const {
	int w;
	int h;

	SDL_RenderGetLogicalSize(_renderer, &w, &h);

	return h;
}

void Renderer::get_size(int *w, int *h) const {
	SDL_RenderGetLogicalSize(_renderer, w, h);
}

void Renderer::set_size(const int w, const int h) const {
	SDL_RenderSetLogicalSize(_renderer, w, h);
}

float Renderer::get_scale_w() const {
	float w;
	float h;

	SDL_RenderGetScale(_renderer, &w, &h);

	return w;
}
float Renderer::get_scale_h() const {
	float w;
	float h;

	SDL_RenderGetScale(_renderer, &w, &h);

	return h;
}
void Renderer::set_scale(const float w, const float h) const {
	SDL_RenderSetScale(_renderer, w, h);
}
void Renderer::get_scale(float *w, float *h) const {
	SDL_RenderGetScale(_renderer, w, h);
}

bool Renderer::get_integer_scaling() const {
	return SDL_RenderGetIntegerScale(_renderer);
}
void Renderer::set_integer_scaling(const bool enable) {
	if (enable)
		SDL_RenderSetIntegerScale(_renderer, SDL_TRUE);
	else
		SDL_RenderSetIntegerScale(_renderer, SDL_FALSE);
}

Rect2 Renderer::get_viewport() const {
	SDL_Rect r;

	SDL_RenderGetViewport(_renderer, &r);

	return Rect2(r.x, r.y, r.w, r.h);
}
void Renderer::set_viewport(const Rect2 &rect) const {
	SDL_Rect r = rect.as_rect();

	SDL_RenderSetViewport(_renderer, &r);
}

Rect2 Renderer::get_clip_rect() const {
	SDL_Rect r;

	SDL_RenderGetClipRect(_renderer, &r);

	return Rect2(r.x, r.y, r.w, r.h);
}
void Renderer::set_clip_rect(Rect2 *rect) const {
	if (rect) {
		SDL_Rect r = rect->as_rect();

		SDL_RenderSetClipRect(_renderer, &r);
	} else {
		SDL_RenderSetClipRect(_renderer, nullptr);
	}
}
bool Renderer::clip_rect_enabled() const {
	return SDL_RenderIsClipEnabled(_renderer);
}

bool Renderer::render_target_supported() {
	return SDL_RenderTargetSupported(_renderer);
}

SDL_Texture *Renderer::get_render_target() {
	return SDL_GetRenderTarget(_renderer);
}
void Renderer::set_render_target(Texture *texture) {
	if (texture) {
		SDL_SetRenderTarget(_renderer, texture->get_texture());
	} else {
		SDL_SetRenderTarget(_renderer, nullptr);
	}
}

void Renderer::initialize() {
	if (SDL_Init(_flags) != 0) {
		printf("SDL_Init() hiba!\n");

		return;
	}

	if (SDL_CreateWindowAndRenderer(_initial_window_width, _initial_window_height, _window_flags, &_window, &_renderer) != 0) {
		printf("SDL_CreateWindowAndRenderer() hiba!\n");

		return;
	}

	_window_display_index = SDL_GetWindowDisplayIndex(_window);
}

void Renderer::destroy() {
	if (_window)
		SDL_DestroyWindow(_window);

	if (_renderer)
		SDL_DestroyRenderer(_renderer);

	_window = nullptr;
	_renderer = nullptr;
}

SDL_Window *Renderer::get_window() {
	return _window;
}

SDL_Renderer *Renderer::get_renderer() {
	return _renderer;
}

Renderer::Renderer() {
	if (_singleton) {
		printf("Renderer::Renderer(): _singleton is not null!\n");
	}

	_initial_window_width = 640;
	_initial_window_height = 480;

	_singleton = this;

	_flags = SDL_INIT_VIDEO | SDL_INIT_TIMER;
	_window_flags = SDL_WINDOW_SHOWN;

	initialize();
}

Renderer::Renderer(unsigned int flags, unsigned int window_flags, int initial_window_width, int initial_window_height) {
	if (_singleton) {
		printf("Renderer::Renderer(flags): _singleton is not null!\n");
	}

	_initial_window_width = initial_window_width;
	_initial_window_height = initial_window_height;

	_singleton = this;

	_flags = flags;
	_window_flags = window_flags;

	initialize();
}

Renderer::~Renderer() {
	if (_singleton != this) {
		printf("Renderer::~Renderer(): _singleton is not this!\n");
	}

	_singleton = nullptr;

	destroy();
}

Renderer *Renderer::get_singleton() {
	return _singleton;
}

Renderer *Renderer::_singleton = nullptr;