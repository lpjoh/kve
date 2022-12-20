#pragma once
#include <string>

namespace kve {
	class Texture {
	private:
#ifdef KVE_DEBUG
		std::string imagePath;
#endif

#ifdef KVE_GL
		unsigned int glTexture;
#endif

		int width = 0, height = 0;

		bool LoadImage(const std::string imagePath);

	public:
#ifdef KVE_DEBUG
		std::string GetImagePath();
#endif

		int hFrames = 1, vFrames = 1;

		int GetWidth();
		int GetHeight();

		void Bind();
		bool Load(const std::string imagePath);

		Texture();
		~Texture();
	};
}