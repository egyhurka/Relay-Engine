#ifndef MESH_H
#define MESH_H

#include <glad/glad.h>

#include "../../Utilities/Color.h"
#include "../Texture/Texture.h"

#include <vector>
#include <optional>

class Mesh {
public: 
	Mesh(std::vector<GLfloat> vertices, std::vector<GLuint> indices, ColorRGB, std::optional<Texture> Texture);
    ~Mesh();
    void draw();
private:
    std::vector<GLfloat> vertices;
    std::vector<GLuint> indices;
    ColorRGB color;
    std::optional<Texture> texture;
    GLuint VAO, VBO, EBO;
};

#endif // !MESH_H
