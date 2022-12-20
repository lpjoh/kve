#pragma once
#include <string>

namespace kve {
	class Texture {
	private:
#ifdef KVE_GL
		unsigned int glTexture;
#endif

		int width = 0, height = 0;

	public:
		int hFrames = 1, vFrames = 1;

		int GetWidth();
		int GetHeight();

		void Bind();
		bool Load(const std::string imagePath);

		Texture();
		~Texture();
	};
}