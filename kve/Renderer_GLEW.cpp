#ifdef KVE_GL

#include "Renderer.h"
#include <iostream>
#include <GL/glew.h>

using namespace kve;

bool Renderer::Start() {
	GLenum glewError = glewInit();
	
	if (glewError != GLEW_OK) {
		std::cerr << "Failed to init GLEW. Error:\n" << glewGetErrorString(glewError) << std::endl;
		return false;
	}

	return true;
}

void Renderer::Clear() {
	glClearColor(
		backgroundColor.r,
		backgroundColor.g,
		backgroundColor.b,
		backgroundColor.a);
	
	glClear(GL_COLOR_BUFFER_BIT);
}

#endif