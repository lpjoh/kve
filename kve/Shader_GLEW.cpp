#ifdef KVE_GL

#include "Shader.h"
#include <iostream>
#include <GL/glew.h>
#include "GL.h"
#include "IO.h"

using namespace kve;

bool Shader::Compile(const std::string sourcePath, unsigned short shaderType) {
	std::optional<std::string> shaderSourceLoad = IO::LoadFileString(sourcePath);

	if (shaderSourceLoad == std::nullopt) {
		std::cerr << "Failed to load shader at \"" << sourcePath << "\"." << std::endl;
		return false;
	}

	std::string shaderSource = shaderSourceLoad.value();

	glShader = glCreateShader(shaderType);

	const char* shaderSource_cstr = shaderSource.c_str();
	glShaderSource(glShader, 1, &shaderSource_cstr, NULL);

	glCompileShader(glShader);

	glGetShaderiv(glShader, GL_COMPILE_STATUS, &GL::success);

	if (!GL::success) {
		glGetShaderInfoLog(glShader, glInfoLogSize, NULL, GL::infoLog);

		std::cerr << "Failed to compile shader at \"" << sourcePath << "\". Error:\n" << GL::infoLog << std::endl;
		return false;
	}

	return true;
}

Shader::~Shader() {
	glDeleteShader(glShader);
}

VertexShader::VertexShader(const std::string sourcePath) {
	Compile(sourcePath, GL_VERTEX_SHADER);
}

FragmentShader::FragmentShader(const std::string sourcePath) {
	Compile(sourcePath, GL_FRAGMENT_SHADER);
}

#endif
