#pragma once
#include "Texture.h"

namespace kve {
	class FrameBuffer {
#ifdef KVE_GL
	private:
		unsigned int glFrameBuffer, glRenderBuffer;
		int width, height;
#endif
	private:
		Texture texture;

		void PreRenderGraphics();

	public:
		Texture* GetTexture();

		void Bind();
		static void Unbind();

		void Start(int width, int height);
		~FrameBuffer();

		void PreRender();
	};
}