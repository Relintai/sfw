#ifndef SCENE_H
#define SCENE_H

//--STRIP
#include "object/reference.h"
#include "render_core/input_event.h"
//--STRIP

class Scene : public Reference {
	SFW_OBJECT(Scene, Reference);

public:
	virtual void input_event(const Ref<InputEvent> &event);
	virtual void update(float delta);
	virtual void render();

	Scene();
	virtual ~Scene();
};

#endif // APPLICATION_H
