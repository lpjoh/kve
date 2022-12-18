#pragma once
#include <glm/glm.hpp>

namespace kve {
	class Renderer {
	public:
		glm::vec4 backgroundColor;

		void Clear();

		bool Start();
	};
}