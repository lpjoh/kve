#ifdef KVE_GL

#include "ShaderProgram.h"
#include <iostream>
#include <GL/glew.h>
#include <glm/gtc/type_ptr.hpp>
#include "GL.h"

using namespace kve;

void ShaderProgram::SetTransform(std::string name, glm::mat4 transform) {
	Use();

	int uniformLocation = glGetUniformLocation(glShaderProgram, name.c_str());
	glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(transform));
}

void ShaderProgram::Attach(Shader* shader) {
	glAttachShader(glShaderProgram, shader->glShader);
}

bool ShaderProgram::Link() {
	glLinkProgram(glShaderProgram);

	glGetProgramiv(glShaderProgram, GL_LINK_STATUS, &GL::success);

	if (!GL::success) {
		glGetProgramInfoLog(glShaderProgram, glInfoLogSize, NULL, GL::infoLog);
		
		std::cerr << "Failed to link shader program. Error:\n" << GL::infoLog << std::endl;
		return false;
	}

	return true;
}

void ShaderProgram::Use() {
	glUseProgram(glShaderProgram);
}

void ShaderProgram::Start() {
	glShaderProgram = glCreateProgram();
}

ShaderProgram::~ShaderProgram() {
	glDeleteProgram(glShaderProgram);
}

#endif