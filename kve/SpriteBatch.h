#pragma once
#include <vector>
#include <glm/glm.hpp>
#include "Mesh.h"
#include "Texture.h"

namespace kve {
	struct BatchedSprite {
		Texture* texture;
		glm::vec2 position, size, srcPosition, srcSize;
	};

	class SpriteBatch {
	private:
		Mesh mesh;
		static ShaderProgram shaderProgram;

		std::vector<BatchedSprite> batchedSprites;

	public:
		void DrawSprite(BatchedSprite batchedSprite);
		
		void Start();
		static void StartStatic();
		
		void Render(glm::mat4 transform = glm::mat4(1.0f));
	};
}