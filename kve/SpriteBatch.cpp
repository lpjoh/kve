#include "SpriteBatch.h"
#include <unordered_map>

using namespace kve;

ShaderProgram SpriteBatch::shaderProgram;

void SpriteBatch::DrawSprite(BatchedSprite batchedSprite) {
	batchedSprites.push_back(batchedSprite);
}

void SpriteBatch::Start() {
	mesh.Start();
}

void SpriteBatch::StartStatic() {
	VertexShader vertexShader("assets/shaders/vertex.glsl");
	FragmentShader fragmentShader("assets/shaders/fragment.glsl");

	shaderProgram.Start();

	shaderProgram.Attach(&vertexShader);
	shaderProgram.Attach(&fragmentShader);

	shaderProgram.Link();
}

void SpriteBatch::Render(glm::mat4 transform) {
	static std::unordered_map<Texture*, std::vector<BatchedSprite>> spriteTextureMap;
	spriteTextureMap.clear();

	for (BatchedSprite& batchedSprite : batchedSprites) {
		if (spriteTextureMap.find(batchedSprite.texture) == spriteTextureMap.end()) {
			spriteTextureMap.emplace(batchedSprite.texture, std::vector<BatchedSprite>());
		}

		spriteTextureMap.at(batchedSprite.texture).push_back(batchedSprite);
	}

	for (auto& textureBatchPair : spriteTextureMap) {
		// A texture and its corresponding sprites
		Texture* texture = textureBatchPair.first;
		std::vector<BatchedSprite>& batchedSpriteList = spriteTextureMap.at(texture);
		
		for (BatchedSprite& batchedSprite : batchedSpriteList) {
			// Find points
			glm::vec2 start = batchedSprite.position;
			glm::vec2 end = start + batchedSprite.size;

			glm::vec2 srcStart = batchedSprite.srcPosition;
			glm::vec2 srcEnd = srcStart + batchedSprite.srcSize;

			float depth = 0.0f;

			mesh.CreateQuad(
				start, end, 0.0f,
				srcStart, srcEnd);
		}

		// Render and reset
		mesh.Load();
		mesh.Render(&shaderProgram, texture, transform);
		mesh.Clear();
	}

	batchedSprites.clear();
}
