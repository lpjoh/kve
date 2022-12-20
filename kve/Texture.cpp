#include "Texture.h"

using namespace kve;

#ifdef KVE_DEBUG

std::string Texture::GetImagePath() {
	return imagePath;
}

#endif


bool Texture::Load(const std::string imagePath) {
#ifdef KVE_DEBUG
	this->imagePath = imagePath;
#endif

	return LoadImage(imagePath);
}

int Texture::GetWidth() {
	return width;
}

int Texture::GetHeight() {
	return height;
}