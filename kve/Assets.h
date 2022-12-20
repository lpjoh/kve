#pragma once
#include <unordered_map>
#include <string>
#include "Texture.h"

namespace kve {
	class Assets {
	private:
		static std::unordered_map<std::string, Texture*> textures;

	public:
		static Texture* LoadTexture(const std::string imagePath);
		static void ClearTextures();

		static void End();
	};
}