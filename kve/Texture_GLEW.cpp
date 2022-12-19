#ifdef KVE_GL

#include "Texture.h"
#include <iostream>
#include <GL/glew.h>
#include <SDL2/SDL_image.h>

using namespace kve;

void kve::Texture::Bind() {
	glBindTexture(GL_TEXTURE_2D, glTexture);
}

bool Texture::Load(std::string imagePath) {
	SDL_Surface* imgSurface = IMG_Load(imagePath.c_str());

	if (imgSurface == nullptr) {
		std::cerr << "Failed to load texture at \"" << imagePath << "\"." << std::endl;
		return false;
	}

	Bind();

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexImage2D(GL_TEXTURE_2D, 0, 3, imgSurface->w, imgSurface->h, 0, GL_RGB, GL_UNSIGNED_BYTE, imgSurface->pixels);
	glGenerateMipmap(GL_TEXTURE_2D);
}

void Texture::Start() {
	glGenTextures(1, &glTexture);
}

#endif