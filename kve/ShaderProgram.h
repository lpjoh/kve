#pragma once
#include <glm/glm.hpp>
#include "Shader.h"

namespace kve {
	class ShaderProgram {
#ifdef KVE_GL
	private:
		unsigned int glShaderProgram;
#endif

	public:
		void SetTransform(std::string name, glm::mat4 transform);

		void Attach(Shader* shader);
		bool Link();
		void Use();

		void Start();
		~ShaderProgram();
	};
}