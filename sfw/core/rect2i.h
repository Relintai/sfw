//--STRIP
#ifndef RECT2I_H
#define RECT2I_H
//--STRIP

/*************************************************************************/
/*  rect2i.h                                                             */
/*  From https://github.com/Relintai/pandemonium_engine (MIT)            */
/*************************************************************************/

//--STRIP
#include "core/vector2i.h" // also includes math_funcs and ustring
#include "core/rect2.h"
//--STRIP

struct _NO_DISCARD_CLASS_ Rect2i {
	Point2i position;
	Size2i size;

	const Point2i &get_position() const { return position; }
	void set_position(const Point2i &p_position) { position = p_position; }
	const Size2i &get_size() const { return size; }
	void set_size(const Size2i &p_size) { size = p_size; }

	int get_area() const { return size.width * size.height; }

	_FORCE_INLINE_ Vector2i get_center() const { return position + (size / 2); }

	inline bool intersects(const Rect2i &p_rect) const {
		if (position.x > (p_rect.position.x + p_rect.size.width)) {
			return false;
		}
		if ((position.x + size.width) < p_rect.position.x) {
			return false;
		}
		if (position.y > (p_rect.position.y + p_rect.size.height)) {
			return false;
		}
		if ((position.y + size.height) < p_rect.position.y) {
			return false;
		}

		return true;
	}

	inline bool encloses(const Rect2i &p_rect) const {
		return (p_rect.position.x >= position.x) && (p_rect.position.y >= position.y) &&
				((p_rect.position.x + p_rect.size.x) < (position.x + size.x)) &&
				((p_rect.position.y + p_rect.size.y) < (position.y + size.y));
	}

	_FORCE_INLINE_ bool has_no_area() const {
		return (size.x <= 0 || size.y <= 0);
	}

	inline Rect2i clip(const Rect2i &p_rect) const { /// return a clipped rect

		Rect2i new_rect = p_rect;

		if (!intersects(new_rect)) {
			return Rect2i();
		}

		new_rect.position.x = MAX(p_rect.position.x, position.x);
		new_rect.position.y = MAX(p_rect.position.y, position.y);

		Point2 p_rect_end = p_rect.position + p_rect.size;
		Point2 end = position + size;

		new_rect.size.x = (int)(MIN(p_rect_end.x, end.x) - new_rect.position.x);
		new_rect.size.y = (int)(MIN(p_rect_end.y, end.y) - new_rect.position.y);

		return new_rect;
	}

	// Returns the instersection between two Rect2is or an empty Rect2i if there is no intersection
	inline Rect2i intersection(const Rect2i &p_rect) const {
		Rect2i new_rect = p_rect;

		if (!intersects(new_rect)) {
			return Rect2i();
		}

		new_rect.position.x = MAX(p_rect.position.x, position.x);
		new_rect.position.y = MAX(p_rect.position.y, position.y);

		Point2i p_rect_end = p_rect.position + p_rect.size;
		Point2i end = position + size;

		new_rect.size.x = MIN(p_rect_end.x, end.x) - new_rect.position.x;
		new_rect.size.y = MIN(p_rect_end.y, end.y) - new_rect.position.y;

		return new_rect;
	}

	inline Rect2i merge(const Rect2i &p_rect) const { ///< return a merged rect

		Rect2i new_rect;

		new_rect.position.x = MIN(p_rect.position.x, position.x);
		new_rect.position.y = MIN(p_rect.position.y, position.y);

		new_rect.size.x = MAX(p_rect.position.x + p_rect.size.x, position.x + size.x);
		new_rect.size.y = MAX(p_rect.position.y + p_rect.size.y, position.y + size.y);

		new_rect.size = new_rect.size - new_rect.position; //make relative again

		return new_rect;
	}

	bool has_point(const Point2i &p_point) const {
		if (p_point.x < position.x) {
			return false;
		}
		if (p_point.y < position.y) {
			return false;
		}

		if (p_point.x >= (position.x + size.x)) {
			return false;
		}
		if (p_point.y >= (position.y + size.y)) {
			return false;
		}

		return true;
	}

	bool operator==(const Rect2i &p_rect) const { return position == p_rect.position && size == p_rect.size; }
	bool operator!=(const Rect2i &p_rect) const { return position != p_rect.position || size != p_rect.size; }

	Rect2i grow(int p_by) const {
		Rect2i g = *this;
		g.position.x -= p_by;
		g.position.y -= p_by;
		g.size.width += p_by * 2;
		g.size.height += p_by * 2;
		return g;
	}

	void grow_by(int p_by) {
		position.x -= p_by;
		position.y -= p_by;
		size.width += p_by * 2;
		size.height += p_by * 2;
	}

	inline Rect2i grow_margin(Margin p_margin, int p_amount) const {
		Rect2i g = *this;
		g = g.grow_individual((MARGIN_LEFT == p_margin) ? p_amount : 0,
				(MARGIN_TOP == p_margin) ? p_amount : 0,
				(MARGIN_RIGHT == p_margin) ? p_amount : 0,
				(MARGIN_BOTTOM == p_margin) ? p_amount : 0);
		return g;
	}

	inline Rect2i grow_side(Side p_side, int p_amount) const {
		Rect2i g = *this;
		g = g.grow_individual((SIDE_LEFT == p_side) ? p_amount : 0,
				(SIDE_TOP == p_side) ? p_amount : 0,
				(SIDE_RIGHT == p_side) ? p_amount : 0,
				(SIDE_BOTTOM == p_side) ? p_amount : 0);
		return g;
	}

	inline Rect2i grow_individual(int p_left, int p_top, int p_right, int p_bottom) const {
		Rect2i g = *this;
		g.position.x -= p_left;
		g.position.y -= p_top;
		g.size.width += p_left + p_right;
		g.size.height += p_top + p_bottom;

		return g;
	}

	_FORCE_INLINE_ Rect2i expand(const Vector2i &p_vector) const {
		Rect2i r = *this;
		r.expand_to(p_vector);
		return r;
	}

	inline void expand_to(const Point2i &p_vector) {
		Point2i begin = position;
		Point2i end = position + size;

		if (p_vector.x < begin.x) {
			begin.x = p_vector.x;
		}
		if (p_vector.y < begin.y) {
			begin.y = p_vector.y;
		}

		if (p_vector.x > end.x) {
			end.x = p_vector.x;
		}
		if (p_vector.y > end.y) {
			end.y = p_vector.y;
		}

		position = begin;
		size = end - begin;
	}

	_FORCE_INLINE_ Rect2i abs() const {
		return Rect2i(Point2i(position.x + MIN(size.x, 0), position.y + MIN(size.y, 0)), size.abs());
	}

	_FORCE_INLINE_ void set_end(const Vector2i &p_end) {
		size = p_end - position;
	}

	_FORCE_INLINE_ Vector2i get_end() const {
		return position + size;
	}

	Rect2 to_rect2() const { return Rect2(position, size); }

	operator String() const;
	operator Rect2() const { return Rect2(position, size); }

	Rect2i(const Rect2 &p_r2) :
			position(p_r2.position),
			size(p_r2.size) {
	}
	Rect2i() {}
	Rect2i(int p_x, int p_y, int p_width, int p_height) :
			position(Point2(p_x, p_y)),
			size(Size2(p_width, p_height)) {
	}
	Rect2i(const Point2 &p_pos, const Size2 &p_size) :
			position(p_pos),
			size(p_size) {
	}
};

//--STRIP
#endif // RECT2_H
//--STRIP
