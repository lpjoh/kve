#ifdef KVE_GL

#include "Shader.h"
#include <iostream>
#include <fstream>
#include <GL/glew.h>
#include "GL.h"

using namespace kve;

bool Shader::Compile(std::string sourcePath, unsigned short shaderType) {
	std::string shaderSource;
	std::ifstream shaderFile(sourcePath);

	if (shaderFile.is_open()) {
		std::string line;

		while (std::getline(shaderFile, line)) {
			shaderSource += line + "\n";
		}

		shaderFile.close();
	}
	else {
		std::cerr << "Failed to load shader at \"" << sourcePath << "\"." << std::endl;
		return false;
	}

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

VertexShader::VertexShader(std::string sourcePath) {
	Compile(sourcePath, GL_VERTEX_SHADER);
}

FragmentShader::FragmentShader(std::string sourcePath) {
	Compile(sourcePath, GL_FRAGMENT_SHADER);
}

#endif
