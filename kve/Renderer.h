#pragma once
#include <glm/glm.hpp>
#include "FrameBuffer.h"
#include "Mesh.h"

namespace kve {
	struct RendererProperties {
		int frameWidth = 640, frameHeight = 480;
	};

	class Engine;

	class Renderer {
	private:
		FrameBuffer frameBuffer;
		Mesh frameMesh;
		ShaderProgram shaderProgram;

		RendererProperties properties;

		glm::mat4 viewTransform;

		bool StartGraphics();
		void UpdateViewTransform();

		Engine* engine;
		friend class Engine;

	public:
		glm::vec4 backgroundColor;

		RendererProperties GetProperties();

		void Clear(glm::vec4 color);

		glm::mat4 GetViewTransform();

		bool Start(RendererProperties properties);
		void Render();
	};
}