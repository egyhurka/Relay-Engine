#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>

#include "../../Utilities/Color.h"

#include <fstream>
#include <sstream>
#include <filesystem>
#include <iostream>
#include <string>

class Shader {
public:
	Shader(const char* vertexPath, const char* fragmentPath);
	void use();
	void setColor(ColorRGB& color);
	GLuint getId() const { return ID; };
private:
	GLuint ID;
	std::string readFile(const char* path);
	void compileShader(GLuint shader, const char* source);
	void setUniform3f(const GLchar* name, GLfloat& v0, GLfloat& v1, GLfloat& v3);
};

#endif // !SHADER_H
