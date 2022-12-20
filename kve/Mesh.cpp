#include "Mesh.h"

using namespace kve;

void Mesh::CreateQuad(glm::vec3 start, glm::vec3 end, glm::vec2 srcStart, glm::vec2 srcEnd) {
	auto& indices = indexBuffer.indices;
	auto& vertices = vertexBuffer.vertices;
	
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

void Mesh::Load() {
	vertexBuffer.Load();
	indexBuffer.Load();
}

void Mesh::Clear() {
	vertexBuffer.vertices.clear();
	indexBuffer.indices.clear();
}