#ifndef GAME_APPLICATION_H
#define GAME_APPLICATION_H

#include "render_core/application.h"

#include "game_scene.h"

class GameApplication : public Application {
	SFW_OBJECT(GameApplication, Application);

public:
	GameApplication() {
		scene = Ref<Scene>(memnew(GameScene()));
	}

	~GameApplication() {
		scene.unref();
	}
};

#endif // GAME_APPLICATION_H
