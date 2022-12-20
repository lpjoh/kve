#include "Sprite.h"

using namespace kve;

Texture* Sprite::GetTexture() {
	return texture;
}

void Sprite::SetTexture(Texture* texture) {
	this->texture = texture;

	srcSize = glm::vec2(1.0f) / glm::vec2(
		(float)texture->hFrames,
		(float)texture->vFrames);

	SetFrame(0);
}

int Sprite::GetFrame() {
	return frame;
}

void Sprite::SetFrame(int frame) {
	this->frame = frame;

	srcPosition = glm::vec2(
		frame % texture->hFrames,
		frame / texture->hFrames) * srcSize;
}

void Sprite::Render(SpriteBatch& spriteBatch) {
	if (texture == nullptr) {
		return;
	}
	
	spriteBatch.DrawSprite(texture, position, size, srcPosition, srcSize);
}