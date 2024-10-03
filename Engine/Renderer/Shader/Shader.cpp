#include "Shader.h"

const char* shaderError = "ERROR::SHADER::";

Shader::Shader(const char* vertexPath, const char* fragmentPath) {
	std::string vertexCode = readFile(vertexPath);
	std::string fragmentCode = readFile(fragmentPath);

	// VERTEX CODE
	GLuint vertex = glCreateShader(GL_VERTEX_SHADER);
	const char* vShaderCode = vertexCode.c_str();
	glShaderSource(vertex, 1, &vShaderCode, NULL);
	compileShader(vertex, vShaderCode);

	// FRAGMENT CODE
	GLuint fragment = glCreateShader(GL_FRAGMENT_SHADER);
	const char* fShaderCode =fragmentCode.c_str();
	glShaderSource(fragment, 1, &fShaderCode, NULL);
	compileShader(fragment, fShaderCode);

	// SHADER PROGRAM
	ID = glCreateProgram();
	glAttachShader(ID, vertex);
	glAttachShader(ID, fragment);
	glLinkProgram(ID);

	glDeleteShader(vertex);
	glDeleteShader(fragment);
}

void Shader::use() {
	glUseProgram(ID);
}

void Shader::setColor(ColorRGB& color) {
	setUniform3f("uColor", color.r, color.g, color.b);
}

void Shader::setMat4(const GLchar* name, const glm::mat4& mat) {
	glUniformMatrix4fv(glGetUniformLocation(ID, name), 1, GL_FALSE, glm::value_ptr(mat));
}

void Shader::setUniform3f(const GLchar* name, GLfloat& v0, GLfloat& v1, GLfloat& v3) {
	GLint loc = glGetUniformLocation(ID, name);
	glUniform3f(loc, v0, v1, v3);
}


std::string Shader::readFile(const char* path) {
	if (!std::filesystem::exists(path)) {
		std::cerr << shaderError << "PATH::FILE_DOES_NOT_EXISTS: " << path << std::endl;
		return "";
	}

	std::ifstream file(path);
	if (!file) {
		std::cerr << shaderError << "PATH::COULD_NOT_OPEN: " << path << std::endl;
		return "";
	}

	std::stringstream buffer;
	buffer << file.rdbuf();

	std::string content = buffer.str();
	if (content.empty()) {
		std::cerr << shaderError << "PATH::FILE_IS_EMPTY" << std::endl;
		return "";
	}

	return content;
}

void Shader::compileShader(GLuint shader, const char* source) {
	glCompileShader(shader);

	int success;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success) {
		char infolog[512];
		glGetShaderInfoLog(shader, 512, nullptr, infolog);
		std::cerr << shaderError << "COMPILE_FAILED: " << infolog << std::endl;
	}
}