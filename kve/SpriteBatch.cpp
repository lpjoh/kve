#include "SpriteBatch.h"

#ifdef KVE_DEBUG
#include <iostream>
#endif

using namespace kve;

ShaderProgram SpriteBatch::shaderProgram;

void SpriteBatch::AddTexture(Texture* texture) {
	batchedSprites.emplace(texture, std::vector<BatchedSprite>());
}

void SpriteBatch::DrawSprite(Texture* texture,
	glm::vec2 position, glm::vec2 size,
	glm::vec2 srcPosition, glm::vec2 srcSize) {
	
#ifdef KVE_DEBUG
	if (batchedSprites.find(texture) == batchedSprites.end()) {
		std::cerr << 
			"Sprite drawn with texture at \"" <<
			texture->GetImagePath() <<
			"\", which was not added to the batch." << std::endl;
		exit(-1);
	}
#endif

	batchedSprites.at(texture).push_back(
		{ position, size, srcPosition, srcSize });
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

	for (auto& textureBatchPair : batchedSprites) {
		// A texture and its corresponding sprites
		Texture* texture = textureBatchPair.first;
		std::vector<BatchedSprite>& batchedSpriteList = batchedSprites.at(texture);
		
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

		batchedSpriteList.clear();
	}
}
