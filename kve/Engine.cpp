#include "Engine.h"

using namespace kve;

void Engine::End() {
	GameEnd();

	window.End();
}

bool Engine::Update() {
	if (!window.Update()) {
		return false;
	}

	if (!GameUpdate(1.0f)) {
		return false;
	}

	Render();

	return true;
}

void Engine::Render() {
	renderer.Clear();

	GameRender();

	window.Render();
}

bool Engine::Start() {
	if (!window.Start(GetWindowProperties())) {
		return false;
	}

	if (!renderer.Start()) {
		return false;
	}

	GameStart();

	while (Update());

	End();
	return true;
}