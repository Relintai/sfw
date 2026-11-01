#ifndef GAME_SCENE_H
#define GAME_SCENE_H

#include "render_core/scene.h"



class GameScene : public Scene {
	SFW_OBJECT(GameScene, Scene);

public:
	virtual void input_event(const Ref<InputEvent> &event);
	virtual void update(float delta);
	virtual void render();

	GameScene();
	~GameScene();

};

#endif
