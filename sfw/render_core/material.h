#ifndef MATERIAL_H
#define MATERIAL_H

#include "core/projection.h"
#include "core/transform.h"
#include "core/transform_2d.h"
#include "object/reference.h"
#include "render_core/shader.h"

class Material : public Reference {
	SFW_OBJECT(Material, Reference);

public:
	void bind();

	virtual void unbind();
	virtual int get_material_id() = 0;
	virtual void bind_uniforms();
	virtual void setup_uniforms();
	virtual void setup_state();
	virtual const GLchar **get_vertex_shader_source() = 0;
	virtual const GLchar **get_fragment_shader_source() = 0;

	GLint get_uniform(const char *name);

	Material();
	virtual ~Material();

protected:
	static Material *current_material;

	Shader *shader;

protected:
	_FORCE_INLINE_ void set_uniform(GLint p_uniform, const Transform &p_transform) {
		const Transform &tr = p_transform;

		GLfloat matrix[16] = { /* build a 16x16 matrix */
			tr.basis.rows[0][0],
			tr.basis.rows[1][0],
			tr.basis.rows[2][0],
			0,
			tr.basis.rows[0][1],
			tr.basis.rows[1][1],
			tr.basis.rows[2][1],
			0,
			tr.basis.rows[0][2],
			tr.basis.rows[1][2],
			tr.basis.rows[2][2],
			0,
			tr.origin.x,
			tr.origin.y,
			tr.origin.z,
			1
		};

		glUniformMatrix4fv(p_uniform, 1, false, matrix);
	}

	_FORCE_INLINE_ void set_uniform(GLint p_uniform, const Transform2D &p_transform) {
		const Transform2D &tr = p_transform;

		GLfloat matrix[16] = { /* build a 16x16 matrix */
			tr.columns[0][0],
			tr.columns[0][1],
			0,
			0,
			tr.columns[1][0],
			tr.columns[1][1],
			0,
			0,
			0,
			0,
			1,
			0,
			tr.columns[2][0],
			tr.columns[2][1],
			0,
			1
		};

		glUniformMatrix4fv(p_uniform, 1, false, matrix);
	}

	_FORCE_INLINE_ void set_uniform(GLint p_uniform, const Projection &p_matrix) {
		GLfloat matrix[16];

		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				matrix[i * 4 + j] = p_matrix.matrix[i][j];
			}
		}

		glUniformMatrix4fv(p_uniform, 1, false, matrix);
	}
};

#endif // MATERIAL_H
