#pragma once
#include <unordered_map>
#include <vector>
#include <glm/glm.hpp>
#include "Mesh.h"
#include "Texture.h"

namespace kve {
	struct BatchedSprite {
		glm::vec2 position, size, srcPosition, srcSize;
	};

	class SpriteBatch {
	private:
		Mesh mesh;
		static ShaderProgram shaderProgram;

		std::unordered_map<Texture*, std::vector<BatchedSprite>> batchedSprites;

	public:
		void AddTexture(Texture* texture);

		void DrawSprite(Texture* texture,
			glm::vec2 position, glm::vec2 size,
			glm::vec2 srcPosition, glm::vec2 srcSize);
		
		void Start();
		static void StartStatic();
		
		void Render(glm::mat4 transform = glm::mat4(1.0f));
	};
}