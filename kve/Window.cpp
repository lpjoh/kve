#include "Window.h"
#include <glm/gtc/matrix_transform.hpp>
#include "Engine.h"

using namespace kve;

void Window::UpdateFrameTransform() {
	float windowAspectRatio = (float)properties.width / (float)properties.height;

	RendererProperties rendererProperties = engine->renderer.GetProperties();
	float frameAspectRatio = 
		(float)rendererProperties.frameWidth / (float)rendererProperties.frameHeight;

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

void Window::Resize(int width, int height) {
    properties.width = width;
    properties.height = height;

    GraphicsResize(width, height);
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
    GraphicsResize(properties.width, properties.height);
}