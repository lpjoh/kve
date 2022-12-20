#pragma once
#include <glm/glm.hpp>
#include "SpriteBatch.h"
#include "Texture.h"

namespace kve {
	class Sprite {
	private:
		Texture* texture = nullptr;

		int frame = 0;
		glm::vec2 srcPosition{}, srcSize{};

	public:
		glm::vec2 position{}, size{};

		Texture* GetTexture();
		void SetTexture(Texture* texture);

		int GetFrame();
		void SetFrame(int frame);

		void Render(SpriteBatch& spriteBatch);
	};
}