#ifdef KVE_GL

#define STB_IMAGE_IMPLEMENTATION
#include "Texture.h"
#include <iostream>
#include <GL/glew.h>
#include <stb_image.h>

using namespace kve;

void Texture::Bind() {
	glBindTexture(GL_TEXTURE_2D, glTexture);
}

void Texture::Unbind() {
	glBindTexture(GL_TEXTURE_2D, 0);
}

bool Texture::Load(const std::string imagePath) {
	int channels;
	unsigned char* data = stbi_load(imagePath.c_str(), &size.x, &size.y, &channels, 0);

	if (data == nullptr) {
		std::cerr << "Failed to load texture at \"" << imagePath << "\"." << std::endl;
		return false;
	}

	Bind();

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, size.x, size.y, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);

	stbi_image_free(data);
}

void Texture::Create(glm::ivec2 size) {
	Bind();

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, size.x, size.y, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);

	this->size = size;
}

void Texture::Start() {
	glGenTextures(1, &glTexture);
}

Texture::~Texture() {
	glDeleteTextures(1, &glTexture);
}

#endif