#pragma once
#include "GraphicsBuffer.h"
#include "ShaderProgram.h"

namespace kve {
	class Mesh {
#ifdef KVE_GL
	private:
		unsigned int glVertexArray;
#endif

	public:
		VertexBuffer vertexBuffer;
		IndexBuffer indexBuffer;

		void Load();
		void Render(ShaderProgram* shaderProgram);

		void Start();
		~Mesh();
	};
}