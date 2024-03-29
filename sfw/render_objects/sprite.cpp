//--STRIP
#include "render_objects/sprite.h"
//--STRIP

void Sprite::render() {
	/*
	mesh_instance->position.x = position.x;
	mesh_instance->position.y = position.y;

	mesh_instance->rotation.z = rotation;

	mesh_instance->scale.x = scale.x;
	mesh_instance->scale.y = scale.y;
	*/

	mesh_instance->transform = transform;
	mesh_instance->render();
}

void Sprite::update_mesh() {
	Ref<Mesh> mesh = mesh_instance->mesh;

	mesh->clear();

	float w2 = width / 2.0;
	float h2 = height / 2.0;

	/*
	mesh->add_uv(region_x, region_y);
	mesh->add_vertex2(-w2, h2);

	mesh->add_uv(region_x + region_width, region_y + region_height);
	mesh->add_vertex2(w2, -h2);

	mesh->add_uv(region_x, region_y + region_height);
	mesh->add_vertex2(-w2, -h2);

	mesh->add_uv(region_x + region_width, region_y);
	mesh->add_vertex2(w2, h2);
	*/

	mesh->add_uv(region_x, region_y);
	mesh->add_vertex2(-w2, -h2);

	mesh->add_uv(region_x + region_width, region_y + region_height);
	mesh->add_vertex2(w2, h2);

	mesh->add_uv(region_x, region_y + region_height);

	mesh->add_vertex2(-w2, h2);

	mesh->add_uv(region_x + region_width, region_y);

	mesh->add_vertex2(w2, -h2);

	mesh->add_triangle(1, 0, 2);
	mesh->add_triangle(0, 1, 3);

	mesh->upload();
}

Sprite::Sprite() {
	mesh_instance = memnew(MeshInstance2D());
	mesh_instance->mesh = Ref<Mesh>(memnew(Mesh(2)));

	width = 1;
	height = 1;

	region_x = 0;
	region_y = 0;
	region_width = 1;
	region_height = 1;
}

Sprite::~Sprite() {
	memdelete(mesh_instance);
}
