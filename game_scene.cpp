#include "game_scene.h"

#include "application.h"

void GameScene::event(const SDL_Event &ev) {
	switch (ev.type) {
		case SDL_WINDOWEVENT: {
			switch (ev.window.event) {
				case SDL_WINDOWEVENT_SIZE_CHANGED: {
					int width = ev.window.data1;
					int height = ev.window.data2;

					float ar = static_cast<float>(width) / static_cast<float>(height);

					camera->width = camera->height * ar;

					glViewport(0, 0, width, height);

					break;
				}
			}

			break;
		}
		case SDL_KEYDOWN: {

			if (ev.key.keysym.scancode == SDL_SCANCODE_A) {
				left = true;
			} else if (ev.key.keysym.scancode == SDL_SCANCODE_W) {
				up = true;
			} else if (ev.key.keysym.scancode == SDL_SCANCODE_S) {
				down = true;
			} else if (ev.key.keysym.scancode == SDL_SCANCODE_D) {
				right = true;
			}

			break;
		}
		case SDL_KEYUP: {

			if (ev.key.keysym.scancode == SDL_SCANCODE_A) {
				left = false;
			} else if (ev.key.keysym.scancode == SDL_SCANCODE_W) {
				up = false;
			} else if (ev.key.keysym.scancode == SDL_SCANCODE_S) {
				down = false;
			} else if (ev.key.keysym.scancode == SDL_SCANCODE_D) {
				right = false;
			}

			break;
		}
	}
}

void GameScene::update(float delta) {
	if (up) {
		sprite->position.y += delta * 3.0;
	}

	if (down) {
		sprite->position.y -= delta * 3.0;
	}

	if (left) {
		sprite->position.x -= delta * 3.0;
	}

	if (right) {
		sprite->position.x += delta * 3.0;
	}

	if (sprite->position.x < 1.5) {
		sprite->position.x = 1.5;
	}

	if (sprite->position.x > 14.5) {
		sprite->position.x = 14.5;
	}

	if (sprite->position.y < 1.5) {
		sprite->position.y = 1.5;
	}

	if (sprite->position.y > 14.5) {
		sprite->position.y = 14.5;
	}
}

void GameScene::render() {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	camera->bind();

	tile_map->render();

	sprite->render();
}

GameScene::GameScene() {
	left = false;
    right = false;
    up = false;
    down = false;

	camera = new OrthographicCamera();
	camera->width = 16;
	camera->height = 16;
	camera->position.x = 8;
	camera->position.y = 8;
	//camera->position.z = -2;

	int w;
	int h;
	SDL_GetWindowSize(Application::get_singleton()->window, &w, &h);

	float ar = static_cast<float>(w) / static_cast<float>(h);
	camera->width = camera->height * ar;

	texture = new Texture();
	texture->load_image("download.bmp");
	//ha a textúrának van alpha csatornája:
	//texture->load_image("download.bmp", GL_RGBA, GL_RGBA);

	material = new TextureMaterial();
	material->texture = texture;

	sprite = new Sprite();
	sprite->mesh_instance->material = material;
	sprite->position.x = 8;
	sprite->position.y = 8;
	sprite->region_x = 7.0 * (1.0 / 16.0);
	sprite->region_y = 7.0 * (1.0 / 16.0);
	sprite->region_width = 1.0 / 16.0;
	sprite->region_height = 1.0 / 16.0;
	sprite->update_mesh();

	tile_map = new TileMap();
	tile_map->material = material;
	tile_map->atlas_size_x = 16;
	tile_map->atlas_size_y = 16;

	tile_map->allocate_data();

	for (int x = 0; x < tile_map->size_x; ++x) {
		for (int y = 0; y < tile_map->size_y; ++y) {
			if (x == 0 || y == 0 || x == tile_map->size_x - 1 || y == tile_map->size_y - 1) {
				tile_map->set_data(x, y, 2);
			} else {
				tile_map->set_data(x, y, 1);
			}
		}
	}

	tile_map->build_mesh();
}

GameScene::~GameScene() {
	delete camera;
	delete texture;
	delete material;
	delete tile_map;
	delete sprite;
}
