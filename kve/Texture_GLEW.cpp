#ifdef KVE_GL

#include "Texture.h"
#include <iostream>
#include <GL/glew.h>
#include <SDL2/SDL_image.h>

using namespace kve;

bool Texture::LoadImage(const std::string imagePath) {
	SDL_Surface* imageSurface = IMG_Load(imagePath.c_str());

	if (imageSurface == nullptr) {
		std::cerr << "Failed to load texture at \"" << imagePath << "\"." << std::endl;
		return false;
	}

	Bind();

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	width = imageSurface->w;
	height = imageSurface->h;

	glTexImage2D(GL_TEXTURE_2D, 0, 3, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, imageSurface->pixels);
	glGenerateMipmap(GL_TEXTURE_2D);

	SDL_FreeSurface(imageSurface);
}

void kve::Texture::Bind() {
	glBindTexture(GL_TEXTURE_2D, glTexture);
}

Texture::Texture() {
	glGenTextures(1, &glTexture);
}

Texture::~Texture() {
	glDeleteTextures(1, &glTexture);
}

#endif