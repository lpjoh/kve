#include "TestEngine.h"
#include <glm/gtc/matrix_transform.hpp>
#include "Assets.h"
#include "TileMap.h"

using namespace kve;

WindowProperties TestEngine::GetWindowProperties() {
	return { 640, 480, "Test engine", true };
}

bool TestEngine::GameStart() {
	renderer.backgroundColor = { 0.0f, 0.0f, 0.5f, 1.0f };

	SpriteBatch::StartStatic();
	spriteBatch.Start();

	Texture* texture1 = Assets::LoadTexture("assets/textures/test.png");
	Texture* texture2 = Assets::LoadTexture("assets/textures/test2.png");
	Texture* texture3 = Assets::LoadTexture("assets/textures/test3.png");

	spriteBatch.AddTexture(texture1);
	spriteBatch.AddTexture(texture2);
	spriteBatch.AddTexture(texture3);

	tileMap.LoadTMX("assets/maps/test.tmx");
	
	return true;
}

void TestEngine::GameRender() {
	tileMap.Render(spriteBatch);
	spriteBatch.Render(window.GetOrthoTransform());
}