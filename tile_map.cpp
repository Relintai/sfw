#include "tile_map.h"

#include "./glm/gtc/matrix_transform.hpp"
#include "./glm/matrix.hpp"
#include "./glm/vec3.hpp"

#include "camera.h"

void TileMap::build_mesh() {
	if (!mesh) {
		mesh = new Mesh(2);
	} else {
		mesh->clear();
	}

	if (!data) {
		//mesh->upload();

		return;
	}

	float asx = 1.0 / atlas_size_x;
	float asy = 1.0 / atlas_size_y;

	for (int x = 0; x < size_x; ++x) {
		int x_offset = x * size_x;

		for (int y = 0; y < size_y; ++y) {
			uint8_t d = data[x_offset + y];

			if (d == 0)
				continue;

			float px;
			float py;

			switch (d) {
				case 1:
					px = 1;
					py = 0;
					break;
				case 2:
					px = 0;
					py = 1;
					break;
			}

			px /= atlas_size_x;
			py /= atlas_size_y;

			add_rect(x, y, px, py, asx, asy);
		}
	}

	mesh->upload();
}

void TileMap::allocate_data() {
	if (size_x <= 0 || size_y <= 0)
		return;

	if (data) {
		delete[] data;
	}

	int size = size_x * size_y;

	data = new uint8_t[size];

	for (int i = 0; i < size; ++i) {
		data[i] = 0;
	}
}

void TileMap::add_rect(const int x, const int y, const float uv_x, const float uv_y, const float uv_size_x, const float uv_size_y) {
	int vc = static_cast<int>(mesh->vertices.size() / mesh->vertex_dimensions);

	mesh->add_uv(uv_x, uv_y);
	mesh->add_vertex2(x, y + 1);

	mesh->add_uv(uv_x + uv_size_x, uv_y + uv_size_y);
	mesh->add_vertex2(x + 1, y);

	mesh->add_uv(uv_x, uv_y + uv_size_y);
	mesh->add_vertex2(x, y);

	mesh->add_uv(uv_x + uv_size_x, uv_y);
	mesh->add_vertex2(x + 1, y + 1);

	mesh->add_triangle(vc + 1, vc + 0, vc + 2);
	mesh->add_triangle(vc + 0, vc + 1, vc + 3);
}

uint8_t TileMap::get_data(const int x, const int y) const {
	//3d-ben: data[(x * size_x * size_x) + (y * size_y) + size_z] etc

	return data[x * size_x + y];
}

void TileMap::set_data(const int x, const int y, const uint8_t value) {
	data[x * size_x + y] = value;
}

void TileMap::render() {
    if (!mesh)
		return;

	glm::mat4 mat_orig = Camera::current_camera->model_view_matrix;
	
	Camera::current_camera->model_view_matrix = glm::translate(Camera::current_camera->model_view_matrix, glm::vec3(position.x, position.y, 0));

	Camera::current_camera->model_view_matrix = glm::rotate(Camera::current_camera->model_view_matrix, rotation, glm::vec3(0, 0, 1));

	Camera::current_camera->model_view_matrix = glm::scale(Camera::current_camera->model_view_matrix, glm::vec3(scale.x, scale.y, 0));

	if (material)
		material->bind();

	mesh->render();

	Camera::current_camera->model_view_matrix = mat_orig;
}

TileMap::TileMap() : Object2D() {
	data = nullptr;
	size_x = 16;
	size_y = 16;

	atlas_size_x = 1;
	atlas_size_y = 1;

	mesh = nullptr;
	material = nullptr;
}
TileMap::~TileMap() {
    if (data)
        delete[] data;
}
