#ifdef KVE_GL

#include "Mesh.h"
#include <GL/glew.h>

using namespace kve;

void Mesh::Render(ShaderProgram* shaderProgram) {
	glBindVertexArray(glVertexArray);

	vertexBuffer.Bind();
	indexBuffer.Bind();

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);
	glEnableVertexAttribArray(0);

	shaderProgram->Use();
	glDrawElements(GL_TRIANGLES, indexBuffer.indices.size() * 3, GL_UNSIGNED_INT, 0);
}

void Mesh::Start() {
	glGenVertexArrays(1, &glVertexArray);

	vertexBuffer.Start();
	indexBuffer.Start();
}

Mesh::~Mesh() {
	glDeleteVertexArrays(1, &glVertexArray);
}

#endif