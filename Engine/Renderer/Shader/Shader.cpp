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

Shader::~Shader() {
	glDeleteProgram(ID);
}

void Shader::use() {
	glUseProgram(ID);
}

void Shader::setColor(ColorRGB& color, float alpha) {
	setUniform4f("uColor", color.r, color.g, color.b, alpha);
}

void Shader::setBool(const GLchar* name, bool value) {
	GLint location = getlocation(name);
	if (location != -1)
		glUniform1i(location, value ? 1 : 0);
}

void Shader::setMat4(const GLchar* name, const glm::mat4& mat) {
	GLint location = getlocation(name);
	if (location != -1)
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(mat));
}

void Shader::setUniform3f(const GLchar* name, GLfloat& v0, GLfloat& v1, GLfloat& v2) {
	GLint location = getlocation(name);
	if (location != -1)
		glUniform3f(location, v0, v1, v2);
}

void Shader::setUniform4f(const GLchar* name, GLfloat& v0, GLfloat& v1, GLfloat& v2, GLfloat& v3) {
	GLint location = getlocation(name);
	if (location != -1)
		glUniform4f(location, v0, v1, v2, v3);
}

bool Shader::getBool(const GLchar* name) {
	GLint location = getlocation(name);
	if (location != -1) {
		GLint value;
		glGetUniformiv(ID, location, &value);
		return static_cast<bool>(value);
	}
	return false;
}

GLint Shader::getlocation(const GLchar* name) {
	GLint location = glGetUniformLocation(ID, name);
	if (location == -1) {
		std::cerr << "ERROR::SHADER::UNIFORM_NOT_FOUND: " << name << std::endl;
		return -1;
	}
	return location;
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