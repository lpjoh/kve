#pragma once
#include "GraphicsBuffer.h"
#include "ShaderProgram.h"
#include "Texture.h"

namespace kve {
	class Mesh {
#ifdef KVE_GL
	private:
		unsigned int glVertexArray;
#endif

	public:
		VertexBuffer vertexBuffer;
		IndexBuffer indexBuffer;

		void CreateQuad(
			glm::vec2 start, glm::vec2 end, float depth,
			glm::vec2 srcStart, glm::vec2 srcEnd);

		void Load();
		void Clear();

		void Start();
		~Mesh();

		void Render(ShaderProgram* shaderProgram, Texture* texture, glm::mat4 transform = glm::mat4(1.0f));
	};
}