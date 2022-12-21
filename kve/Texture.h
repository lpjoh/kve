#pragma once
#include <string>
#include <glm/glm.hpp>

namespace kve {
	class Texture {
#ifdef KVE_GL
	private:
		unsigned int glTexture;
#endif
	private:
		glm::ivec2 size = { 0, 0 };

		friend class FrameBuffer;

	public:
		glm::ivec2 frameCounts = { 1, 1 };

		glm::ivec2 GetSize();

		void Bind();
		static void Unbind();

		bool Load(const std::string imagePath);
		void Create(glm::ivec2 size);

		void Start();
		~Texture();
	};
}