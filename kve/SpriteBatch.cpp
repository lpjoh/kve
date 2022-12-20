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
	auto& indices = mesh.indexBuffer.indices;
	auto& vertices = mesh.vertexBuffer.vertices;

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

			// Create vertices
			float depth = 0.0f;

			vertices.push_back({
				{ start.x, start.y, depth },
				{ srcStart.x, srcStart.y } });

			vertices.push_back({
				{ end.x, start.y, depth },
				{ srcEnd.x, srcStart.y } });

			vertices.push_back({
				{ start.x, end.y, depth },
				{ srcStart.x, srcEnd.y } });

			vertices.push_back({
				{ end.x, end.y, depth },
				{ srcEnd.x, srcEnd.y } });

			// Create indices
			int first_index = vertices.size() - 4;

			indices.push_back(
				{ first_index, first_index + 1, first_index + 2 });

			indices.push_back(
				{ first_index + 1, first_index + 2, first_index + 3 });
		}

		// Render and reset
		mesh.Load();
		mesh.Render(&shaderProgram, texture, transform);
		mesh.Clear();
	}

	batchedSprites.clear();
}
