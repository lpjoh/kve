#include "TestEngine.h"

using namespace kve;

bool TestEngine::GameStart() {
	renderer.backgroundColor = { 0.0f, 0.0f, 0.5f, 1.0f };

	texture1.Start();
	texture1.Load("assets/textures/test1.png");

	texture2.Start();
	texture2.Load("assets/textures/test2.png");

	SpriteBatch::StartStatic();
	spriteBatch.Start();

	textureID1 = spriteBatch.AddTexture(&texture1);
	textureID2 = spriteBatch.AddTexture(&texture2);
	
	return true;
}

void TestEngine::GameRender() {
	static float time = 0.0f;

	spriteBatch.DrawSprite(textureID1,
		{ time, time }, { 0.5f, 0.5f },
		{ 0.0f, 0.0f }, { 1.0f, 1.0f });

	spriteBatch.DrawSprite(textureID2,
		{ -time, time }, { 0.5f, 0.5f },
		{ 0.0f, 0.0f }, { 1.0f, 1.0f });

	spriteBatch.DrawSprite(textureID1,
		{ -time, -time }, { 0.5f, 0.5f },
		{ 0.0f, 0.0f }, { 1.0f, 1.0f });

	spriteBatch.DrawSprite(textureID2,
		{ time, -time }, { 0.5f, 0.5f },
		{ 0.0f, 0.0f }, { 1.0f, 1.0f });
	
	spriteBatch.Render();

	time += 0.001f;
}
