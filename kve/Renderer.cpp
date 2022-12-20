#include "Renderer.h"
#include "Engine.h"
#include <glm/gtc/matrix_transform.hpp>

using namespace kve;

void Renderer::UpdateViewTransform() {
	viewTransform = 
		glm::ortho(0.0f,
			float(properties.frameWidth), float(properties.frameHeight),
			0.0f, -1.0f, 1.0f);
}

RendererProperties Renderer::GetProperties() {
	return properties;
}

glm::mat4 Renderer::GetViewTransform() {
	return viewTransform;
}

bool Renderer::Start(RendererProperties properties) {
	this->properties = properties;

	if (!StartGraphics()) {
		return false;
	}

	frameBuffer.Start(properties.frameWidth, properties.frameHeight);
	
	frameMesh.Start();

	frameMesh.CreateQuad(
		glm::vec3(-1.0f, -1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 0.0f),
		glm::vec2(0.0f, 0.0f), glm::vec2(1.0f, 1.0f));

	frameMesh.Load();

	VertexShader vertexShader("assets/shaders/vertex.glsl");
	FragmentShader fragmentShader("assets/shaders/fragment.glsl");

	shaderProgram.Start();

	shaderProgram.Attach(&vertexShader);
	shaderProgram.Attach(&fragmentShader);

	shaderProgram.Link();

	UpdateViewTransform();

	return true;
}

void Renderer::Render() {
	frameBuffer.Bind();
	frameBuffer.PreRender();

	Clear(backgroundColor);
	engine->GameRender();

	FrameBuffer::Unbind();

	engine->window.PreRender();

	shaderProgram.Use();

	frameMesh.Render(
		&shaderProgram, &frameBuffer.texture, engine->window.GetFrameTransform());
}