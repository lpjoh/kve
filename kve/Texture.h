#pragma once
#include <string>

namespace kve {
	class Texture {
#ifdef KVE_GL
	private:
		unsigned int glTexture;
#endif
	public:
		void Bind();
		bool Load(std::string imagePath);

		void Start();
	};
}