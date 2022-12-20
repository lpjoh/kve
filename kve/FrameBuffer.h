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

		friend class Renderer;

	public:
		void Bind();
		static void Unbind();

		void Start(int width, int height);
		~FrameBuffer();

		void PreRender();
	};
}