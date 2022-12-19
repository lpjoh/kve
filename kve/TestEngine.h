#pragma once
#include "Engine.h"
#include "SpriteBatch.h"
#include "Texture.h"

namespace kve {
	class TestEngine : public Engine {
	private:
		SpriteBatch spriteBatch;

		Texture texture1, texture2;
		int textureID1, textureID2;

	public:
		bool GameStart() override;
		void GameRender() override;
	};
}