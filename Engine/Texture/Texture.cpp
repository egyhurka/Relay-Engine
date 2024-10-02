#include "Texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <iostream>

Texture::Texture(const char* image, GLenum texType, GLenum slot, GLenum format, GLenum pixelType) : ID(0), type(texType) {
    int widthImg, heightImg, numColCh;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* bytes = stbi_load(image, &widthImg, &heightImg, &numColCh, 0);

    if (!bytes) {
        std::cerr << "ERROR::TEXTURE::FAILED_TO_LOAD: " << image << std::endl;
        return;
    }

    glGenTextures(1, &ID);
    glActiveTexture(slot);
    glBindTexture(texType, ID);

    glTexParameteri(texType, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
    glTexParameteri(texType, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexParameteri(texType, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(texType, GL_TEXTURE_WRAP_T, GL_REPEAT);

    GLenum internalFormat = (numColCh == 4) ? GL_RGBA : GL_RGB;
    glTexImage2D(texType, 0, internalFormat, widthImg, heightImg, 0, format, pixelType, bytes);
    glGenerateMipmap(texType);

    stbi_image_free(bytes);
    glBindTexture(texType, 0);
}

void Texture::texUnit(Shader* shader, const char* uniform, GLuint unit) {
    GLuint texUni = glGetUniformLocation(shader->getId(), uniform);
    glUniform1i(texUni, unit);
}

void Texture::bind() {
    glBindTexture(type, ID);
}

void Texture::unBind() {
    glBindTexture(type, 0);
}

void Texture::deleteTex() {
    glDeleteTextures(1, &ID);
}