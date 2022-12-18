#pragma once
#include <string>

namespace kve {
	class Shader {
#ifdef KVE_GL
	private:
		unsigned int glShader;

	protected:
		bool Compile(std::string sourcePath, unsigned short shaderType);
#endif
	private:
		friend class ShaderProgram;
	
	public:
		~Shader();
	};

	class VertexShader : public Shader {
	public:
		VertexShader(std::string sourcePath);
	};

	class FragmentShader : public Shader {
	public:
		FragmentShader(std::string sourcePath);
	};
}