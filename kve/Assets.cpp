#include "Assets.h"
#include <filesystem>

using namespace kve;

std::unordered_map<std::string, Texture> Assets::textures;

Texture* Assets::LoadTexture(const std::string imagePath) {
	// Get canonical image path, for finding duplicates
	std::filesystem::path imageFsPath(imagePath);
	imageFsPath = std::filesystem::canonical(imageFsPath);

	std::string canonImagePath = imageFsPath.generic_string();

	if (textures.find(canonImagePath) == textures.end()) {
		// Texture does not exist, load
		textures.emplace(canonImagePath, Texture());
		Texture& texture = textures.at(canonImagePath);

		texture.Load(canonImagePath);
	}

	return &textures.at(canonImagePath);
}