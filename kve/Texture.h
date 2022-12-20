#pragma once
#include <string>

namespace kve {
	class Texture {
#ifdef KVE_GL
	private:
		unsigned int glTexture;
#endif
	private:
		int width = 0, height = 0;

		friend class FrameBuffer;

	public:
		int hFrames = 1, vFrames = 1;

		int GetWidth();
		int GetHeight();

		void Bind();
		static void Unbind();

		bool Load(const std::string imagePath);
		void Create(int width, int height);

		void Start();
		~Texture();
	};
}