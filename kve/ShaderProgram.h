#pragma once
#include "Shader.h"

namespace kve {
	class ShaderProgram {
#ifdef KVE_GL
	private:
		unsigned int glShaderProgram;
#endif

	public:
		void Attach(Shader* shader);
		bool Link();
		void Use();

		void Start();
		~ShaderProgram();
	};
}