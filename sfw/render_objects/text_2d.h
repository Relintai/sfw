#ifndef TEXT_2D_H
#define TEXT_2D_H

#include "core/color.h"
#include "core/ustring.h"
#include "core/vector2.h"

#include "object/reference.h"

#include "object_2d.h"

class Font;
class FontMaterial;
class Mesh;

class Text2D : public Object2D {
	SFW_OBJECT(Text2D, Object2D);

public:
	Color get_text_color() const;
	void set_text_color(const Color &p_color);

	String get_text() const;
	void set_text(const String &p_text);

	Ref<Font> get_font() const;
	void set_font(const Ref<Font> &p_font);

	Vector2 get_text_size();

	void update();
	void render();

	Text2D();
	~Text2D();

protected:
	Ref<Font> _font;
	Ref<FontMaterial> _material;
	Ref<Mesh> _mesh;
	String _text;
	Color _text_color;
	Vector2 _text_size;
};

#endif // MESH_INSTACE_H
