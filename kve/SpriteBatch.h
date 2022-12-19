#pragma once
#include <vector>
#include <glm/glm.hpp>
#include "Mesh.h"
#include "Texture.h"

namespace kve {
	struct BatchedSprite {
		int textureIndex;
		glm::vec2 position, size, srcPosition, srcSize;
	};

	class SpriteBatch {
	private:
		Mesh mesh;
		static ShaderProgram shaderProgram;

		std::vector<std::vector<BatchedSprite>> batchedSprites;
		std::vector<Texture*> textures;

	public:
		int AddTexture(Texture* texture);

		void DrawSprite(int textureIndex,
			glm::vec2 position, glm::vec2 size,
			glm::vec2 srcPosition, glm::vec2 srcSize);
		
		void Start();
		static void StartStatic();
		
		void Render();
	};
}