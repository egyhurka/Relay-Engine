#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

#include "../../Utilities/Color.h"

#include <fstream>
#include <sstream>
#include <filesystem>
#include <iostream>
#include <string>

class Shader {
public:
	Shader(const char* vertexPath, const char* fragmentPath);
	~Shader();

	void use();
	void setColor(ColorRGB& color, float alpha);

	void setBool(const GLchar* name, bool value);
	void setMat4(const GLchar* name, const glm::mat4& mat);
	void setUniform3f(const GLchar* name, GLfloat& v0, GLfloat& v1, GLfloat& v2);
	void setUniform4f(const GLchar* name, GLfloat& v0, GLfloat& v1, GLfloat& v3, GLfloat& v4);

	bool getBool(const GLchar* name);

	inline const GLuint getId() const { return ID; };
private:
	GLuint ID;
	std::string readFile(const char* path);
	GLint getlocation(const GLchar* name);
	void compileShader(GLuint shader, const char* source);
};

#endif // !SHADER_H
