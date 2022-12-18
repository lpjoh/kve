#ifdef KVE_GL

#include "GraphicsBuffer.h"
#include <GL/glew.h>

using namespace kve;

void GraphicsBuffer::Start() {
	glGenBuffers(1, &glBuffer);
}

GraphicsBuffer::~GraphicsBuffer() {
	glDeleteBuffers(1, &glBuffer);
}

void VertexBuffer::Bind() {
	glBindBuffer(GL_ARRAY_BUFFER, glBuffer);
}

void VertexBuffer::Load() {
	Bind();
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);
}

void IndexBuffer::Bind() {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, glBuffer);
}

void IndexBuffer::Load() {
	Bind();
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(glm::ivec3), indices.data(), GL_STATIC_DRAW);
}

#endif