#pragma once
#include "Engine.h"
#include "ShaderProgram.h"
#include "Mesh.h"

namespace kve {
	class TestEngine : public Engine {
	private:
		Mesh mesh;
		ShaderProgram shaderProgram;

	public:
		bool GameStart() override;
		void GameRender() override;
	};
}