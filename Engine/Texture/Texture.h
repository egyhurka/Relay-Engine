#ifndef TEXTURE_H
#define TEXTURE_H

#include <glad/glad.h>

#include "../Renderer/Shader/Shader.h"

class Texture {
public:
	Texture(const char* image, GLenum texType, GLenum slot, GLenum format, GLenum pixelType);

	void texUnit(Shader* shader, const char* uniform, GLuint unit);
	void bind();
	void unBind();
	void deleteTex();
private:
	GLuint ID;
	GLenum type;
};

#endif // !TEXTURE_H
