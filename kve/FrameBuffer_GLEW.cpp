#ifdef KVE_GL

#include "FrameBuffer.h"
#include <iostream>
#include <GL/glew.h>

using namespace kve;

void FrameBuffer::PreRenderGraphics() {
	glViewport(0, 0, size.x, size.y);
}

void FrameBuffer::Bind() {
	glBindFramebuffer(GL_FRAMEBUFFER, glFrameBuffer);
	glBindRenderbuffer(GL_RENDERBUFFER, glRenderBuffer);
}

void FrameBuffer::Unbind() {
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);
}

void FrameBuffer::Start(glm::ivec2 size) {
	glGenFramebuffers(1, &glFrameBuffer);
	glGenRenderbuffers(1, &glRenderBuffer);
	
	Bind();

	texture.Start();
	texture.Create(size);

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture.glTexture, 0);

	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, size.x, size.y);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, glRenderBuffer);

	FrameBuffer::Unbind();
	Texture::Unbind();

	this->size = size;
}

FrameBuffer::~FrameBuffer() {
	glDeleteRenderbuffers(1, &glRenderBuffer);
	glDeleteFramebuffers(1, &glFrameBuffer);
}

#endif