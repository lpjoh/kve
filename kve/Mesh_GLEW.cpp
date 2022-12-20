#ifdef KVE_GL

#include "Mesh.h"
#include <GL/glew.h>

using namespace kve;

void Mesh::Start() {
	glGenVertexArrays(1, &glVertexArray);

	vertexBuffer.Start();
	indexBuffer.Start();
}

Mesh::~Mesh() {
	glDeleteVertexArrays(1, &glVertexArray);
}

void Mesh::Render(ShaderProgram* shaderProgram, Texture* texture, glm::mat4 transform) {
	glBindVertexArray(glVertexArray);

	vertexBuffer.Bind();
	indexBuffer.Bind();

	// Position
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
	glEnableVertexAttribArray(0);

	// UV
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));
	glEnableVertexAttribArray(1);

	shaderProgram->SetTransform("transform", transform);

	glActiveTexture(GL_TEXTURE0);
	texture->Bind();

	shaderProgram->Use();

	glDrawElements(GL_TRIANGLES, indexBuffer.indices.size() * 3, GL_UNSIGNED_INT, 0);

	Texture::Unbind();
}

#endif