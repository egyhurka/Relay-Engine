#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <iostream>
#include <string>

class Shader {
public:
	Shader(const char* vertexPath, const char* fragmentPath);
	void use();
private:
	GLuint ID;
	std::string readFile(const char* path);
	void compileShader(GLuint shader, const char* source);
};

#endif // !SHADER_H
