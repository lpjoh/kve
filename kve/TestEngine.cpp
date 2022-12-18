#include "TestEngine.h"

using namespace kve;

bool TestEngine::GameStart() {
	renderer.backgroundColor = { 0.0f, 0.0f, 0.5f, 1.0f };

	VertexShader vertexShader("vertex.glsl");
	FragmentShader fragmentShader("fragment.glsl");

	shaderProgram.Start();

	shaderProgram.Attach(&vertexShader);
	shaderProgram.Attach(&fragmentShader);

	shaderProgram.Link();
	
	mesh.Start();

	auto& vertices = mesh.vertexBuffer.vertices;

	vertices.push_back({ { 0.5f,  0.5f, 0.0f } });
	vertices.push_back({ { 0.5f, -0.5f, 0.0f } });
	vertices.push_back({ { -0.5f, -0.5f, 0.0f } });
	vertices.push_back({ { -0.5f,  0.5f, 0.0f } });

	IndexBuffer indexBuffer;

	auto& indices = mesh.indexBuffer.indices;

	indices.push_back({ 0, 1, 3 });
	indices.push_back({ 1, 2, 3 });

	mesh.Load();

	return true;
}

void TestEngine::GameRender() {
	mesh.Render(&shaderProgram);
}
