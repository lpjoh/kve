#include "Mesh.h"

using namespace kve;

void Mesh::Load() {
	vertexBuffer.Load();
	indexBuffer.Load();
}

void Mesh::Clear() {
	vertexBuffer.vertices.clear();
	indexBuffer.indices.clear();
}