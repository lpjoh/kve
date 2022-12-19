#include "SpriteBatch.h"

using namespace kve;

ShaderProgram SpriteBatch::shaderProgram;

int SpriteBatch::AddTexture(Texture* texture) {
	textures.push_back(texture);
	batchedSprites.push_back(std::vector<BatchedSprite>());

	return textures.size() - 1;
}

void SpriteBatch::DrawSprite(int textureIndex,
	glm::vec2 position, glm::vec2 size,
	glm::vec2 srcPosition, glm::vec2 srcSize) {
	
	batchedSprites[textureIndex].push_back(
		{ textureIndex, position, size, srcPosition, srcSize });
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

void SpriteBatch::Render() {
	auto& indices = mesh.indexBuffer.indices;
	auto& vertices = mesh.vertexBuffer.vertices;

	for (int textureID = 0; textureID < batchedSprites.size(); textureID++) {
		std::vector<BatchedSprite>& bsList = batchedSprites[textureID];
		
		for (BatchedSprite& bs : bsList) {
			glm::vec2 start = bs.position;
			glm::vec2 end = start + bs.size;

			glm::vec2 srcStart = bs.srcPosition;
			glm::vec2 srcEnd = srcStart + bs.srcSize;

			vertices.push_back({
				{ start.x, start.y, 0.0f },
				{ srcStart.x, srcStart.y } });

			vertices.push_back({
				{ end.x, start.y, 0.0f },
				{ srcEnd.x, srcStart.y } });

			vertices.push_back({
				{ start.x, end.y, 0.0f },
				{ srcStart.x, srcEnd.y } });

			vertices.push_back({
				{ end.x, end.y, 0.0f },
				{ srcEnd.x, srcEnd.y } });

			int first_index = vertices.size() - 4;

			indices.push_back(
				{ first_index, first_index + 1, first_index + 2 });

			indices.push_back(
				{ first_index + 1, first_index + 2, first_index + 3 });

			mesh.Load();
			mesh.Render(&shaderProgram, textures[textureID]);

			mesh.Clear();
		}

		bsList.clear();
	}
}
