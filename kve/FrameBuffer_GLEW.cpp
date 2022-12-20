#ifdef KVE_GL

#include "FrameBuffer.h"
#include <iostream>
#include <GL/glew.h>

using namespace kve;

void FrameBuffer::PreRenderGraphics() {
	glViewport(0, 0, width, height);
}

void FrameBuffer::Bind() {
	glBindFramebuffer(GL_FRAMEBUFFER, glFrameBuffer);
	glBindRenderbuffer(GL_RENDERBUFFER, glRenderBuffer);
}

void FrameBuffer::Unbind() {
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);
}

void FrameBuffer::Start(int width, int height) {
	glGenFramebuffers(1, &glFrameBuffer);
	glGenRenderbuffers(1, &glRenderBuffer);
	
	Bind();

	texture.Start();
	texture.Create(width, height);

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture.glTexture, 0);

	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, glRenderBuffer);

	FrameBuffer::Unbind();
	Texture::Unbind();

	this->width = width;
	this->height = height;
}

FrameBuffer::~FrameBuffer() {
	glDeleteRenderbuffers(1, &glRenderBuffer);
	glDeleteFramebuffers(1, &glFrameBuffer);
}

#endif