#pragma once
#include <vector>
#include <glm/glm.hpp>

namespace kve {
	class GraphicsBuffer {
#ifdef KVE_GL
	protected:
		unsigned int glBuffer;
#endif
	public:
		void Start();
		~GraphicsBuffer();
	};

	struct Vertex {
		glm::vec3 position;
		glm::vec2 uv;
	};

	class VertexBuffer : public GraphicsBuffer {
	public:
		std::vector<Vertex> vertices;

		void Bind();
		void Load();
	};

	class IndexBuffer : public GraphicsBuffer {
	public:
		std::vector<glm::ivec3> indices;

		void Bind();
		void Load();
	};
}