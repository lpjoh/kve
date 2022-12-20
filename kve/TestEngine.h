#pragma once
#include "Engine.h"
#include "SpriteBatch.h"
#include "Texture.h"
#include "TileMap.h"

namespace kve {
	class TestEngine : public Engine {
	private:
		Texture texture;
		SpriteBatch spriteBatch;

		TileMap tileMap;

	public:
		WindowProperties GetWindowProperties() override;

		bool GameStart() override;
		bool GameUpdate(float delta) override;
		void GameRender() override;
	};
}