#ifdef KVE_GL

#include "Renderer.h"
#include <iostream>
#include <GL/glew.h>

using namespace kve;

bool Renderer::StartGraphics() {
	GLenum glewError = glewInit();

	if (glewError != GLEW_OK) {
		std::cerr << "Failed to init GLEW. Error:\n" << glewGetErrorString(glewError) << std::endl;
		return false;
	}

	return true;
}

void Renderer::Clear(glm::vec4 color) {
	glClearColor(
		color.r,
		color.g,
		color.b,
		color.a);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

#endif