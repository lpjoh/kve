#include "Window.h"
#include <glm/gtc/matrix_transform.hpp>
#include "Engine.h"

using namespace kve;

void Window::UpdateFrameTransform() {
	float windowAspectRatio = (float)properties.size.x / (float)properties.size.y;

	RendererProperties rendererProperties = engine->renderer.GetProperties();

	glm::vec2 frameSize = glm::vec2(rendererProperties.frameSize);
	float frameAspectRatio = frameSize.x / frameSize.y;

	if (windowAspectRatio > frameAspectRatio) {
		float aspectRatio = frameAspectRatio / windowAspectRatio;

		frameTransform =
			glm::scale(glm::mat4(1.0f), glm::vec3(aspectRatio, 1.0f, 0.0f));
	}
	else {
		float aspectRatio = windowAspectRatio / frameAspectRatio;

		frameTransform =
			glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, aspectRatio, 0.0f));
	}
}

void Window::Resize(glm::ivec2 size) {
    properties.size = size;

    GraphicsResize(size);
	UpdateFrameTransform();
}

WindowProperties Window::GetProperties() {
    return properties;
}

glm::mat4 Window::GetFrameTransform() {
	return frameTransform;
}

bool Window::Start(WindowProperties properties) {
	this->properties = properties;

	if (!StartGraphics()) {
		return false;
	}

	return true;
}

void Window::PreRender() {
    GraphicsResize(properties.size);
}