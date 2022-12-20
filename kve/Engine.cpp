#include "Engine.h"
#include "Assets.h"

using namespace kve;

void Engine::End() {
	GameEnd();

	Assets::End();
	window.End();
}

bool Engine::Update() {
	if (!window.Update()) {
		return false;
	}

	if (!GameUpdate(window.GetDeltaTime())) {
		return false;
	}

	Render();

	window.Sleep();

	return true;
}

void Engine::Render() {
	renderer.Render();
	window.Render();
}

bool Engine::Start() {
	window.engine = this;
	renderer.engine = this;

	if (!window.Start(GetWindowProperties())) {
		return false;
	}

	if (!renderer.Start(GetRendererProperties())) {
		return false;
	}

	window.UpdateFrameTransform();

	GameStart();

	while (Update());

	End();
	return true;
}