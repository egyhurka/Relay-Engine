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
	Mesh(std::vector<GLfloat> vertices, std::vector<GLuint> indices, ColorRGB color, std::optional<Texture> Texture);
    virtual ~Mesh();

    void rotate(float rotationSpeed, float deltaTime, glm::vec3 axis);
    void translate(glm::vec3 position);
    virtual void draw();

    ColorRGB getColor() const { return color; };
    std::optional<Texture> getTexture() const { return texture; }
    
    inline const glm::mat4& getModelMatrix() const { return modelMatrix; };
private:
    glm::mat4 modelMatrix;
    std::vector<GLfloat> vertices;
    std::vector<GLuint> indices;
    std::optional<Texture> texture;
    ColorRGB color;
    GLuint VAO, VBO, EBO;

    void setupMesh(std::vector<GLfloat> vertices, std::vector<GLuint> indices);
};

class CubeMesh : public Mesh {
public:
    CubeMesh(ColorRGB color, std::optional<Texture> Texture);

private:
    inline std::vector<GLfloat> createCubeVertices() const {
        return {
            -0.5f, -0.5f, -0.5f,
             0.5f, -0.5f, -0.5f,
             0.5f,  0.5f, -0.5f,
            -0.5f,  0.5f, -0.5f,
            -0.5f, -0.5f,  0.5f,
             0.5f, -0.5f,  0.5f,
             0.5f,  0.5f,  0.5f,
            -0.5f,  0.5f,  0.5f
        };
    };

    inline std::vector<GLuint> createCubeIndices() const {
        return {
           0, 1, 2, 0, 2, 3, // back
           4, 5, 6, 4, 6, 7, // front
           0, 1, 5, 0, 5, 4, // left
           2, 3, 7, 2, 7, 6, // right
           3, 0, 4, 3, 4, 7, // top
           1, 2, 6, 1, 6, 5  // bottom
        };
    }
};

#endif // !MESH_H