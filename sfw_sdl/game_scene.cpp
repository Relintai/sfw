#include "game_scene.h"

#include "render_core/application.h"

#include "render_core/app_window.h"

#include "render_core/3rd_glad.h"

void GameScene::input_event(const Ref<InputEvent> &event) {
	ERR_PRINT(event->as_text());
}

void GameScene::update(float delta) {
}

void GameScene::render() {
	AppWindow::get_singleton()->reset_viewport();

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

GameScene::GameScene() {
}

GameScene::~GameScene() {
}
