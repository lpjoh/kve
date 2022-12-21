#pragma once
#include "Texture.h"
#include <glm/glm.hpp>

namespace kve {
	class FrameBuffer {
#ifdef KVE_GL
	private:
		unsigned int glFrameBuffer, glRenderBuffer;
		glm::ivec2 size;
#endif
	private:
		Texture texture;

		void PreRenderGraphics();

	public:
		Texture* GetTexture();

		void Bind();
		static void Unbind();

		void Start(glm::ivec2 size);
		~FrameBuffer();

		void PreRender();
	};
}