#include "TestEngine.h"
#include <iostream>
#include "Assets.h"
#include "TileMap.h"

using namespace kve;

WindowProperties TestEngine::GetWindowProperties() {
	return { 640, 480, "Test engine", true, 60.0f };
}

RendererProperties TestEngine::GetRendererProperties() {
	return { 640, 360 };
}

bool TestEngine::GameStart() {
	renderer.backgroundColor = { 0.0f, 0.0f, 0.5f, 1.0f };

	SpriteBatch::StartStatic();
	spriteBatch.Start();

	tileMap.LoadTMX("assets/maps/test.tmx");
	
	return true;
}

bool TestEngine::GameUpdate(float delta) {
	std::cout << delta << std::endl;

	return true;
}

void TestEngine::GameRender() {
	tileMap.Render(spriteBatch);
	spriteBatch.Render(renderer.GetViewTransform());
}