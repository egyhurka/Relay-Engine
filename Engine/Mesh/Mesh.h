#ifndef MESH_H
#define MESH_H

#include <glad/glad.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

#include "../../Utilities/Color.h"
#include "../Texture/Texture.h"
#include "../Renderer/Shader/Shader.h"

#include <vector>
#include <optional>

class Mesh {
public: 
	Mesh(std::vector<GLfloat> vertices, std::vector<GLuint> indices, ColorRGB, std::optional<Texture> Texture);
    ~Mesh();
    void scale(float scaleFactor);
    void rotate(float angle, const glm::vec3& axis);
    void draw();
    const glm::mat4& getModelMatrix() const { return modelMatrix; };
    ColorRGB getColor() const { return color; };
    std::optional<Texture> getTexture() const { return texture; }
private:
    glm::mat4 modelMatrix;
    std::vector<GLfloat> vertices;
    std::vector<GLuint> indices;
    ColorRGB color;
    std::optional<Texture> texture;
    GLuint VAO, VBO, EBO;
};

#endif // !MESH_H
