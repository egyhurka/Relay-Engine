#ifndef MESH_H
#define MESH_H

#include <glad/glad.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

#include "../../Utilities/Color.h"
#include "../../Utilities/Util.h"
#include "../Texture/Texture.h"
#include "../Renderer/Shader/Shader.h"

#include "InstancedObject.h"

#include <vector>
#include <optional>

class Mesh {
public: 
    Mesh(std::vector<Vertex> vertices, std::vector<GLuint> indices, ColorRGB color, std::optional<Texture> texture);
    ~Mesh();

    bool isTransparent = false;

    void rotate(float rotationSpeed, float deltaTime, glm::vec3 axis);
    void scale(float scaleFactor);
    void translate(glm::vec3 position);

    void draw(Shader* shader);

    inline void setColor(ColorRGB color) { this->color = color; };

    inline ColorRGB getColor() const { return color; };
    inline const std::optional<Texture> getTexture() const { return texture; };
    inline const glm::mat4& getModelMatrix() const { return modelMatrix; };
    inline const GLuint getVAO() const { return VAO; };
    inline const GLuint getVertexCount() const { return static_cast<GLuint>(indices.size()); };
    inline const std::unique_ptr<Mesh> clone() { return std::make_unique<Mesh>(vertices, indices, color, texture); };

    static inline const std::vector<Vertex> createCubeVertices() {
        std::vector<Vertex> vertices = {
            // POSITION                         // COLOR                         // NORMAL
            {glm::vec3(-0.5f, -0.5f, -0.5f),   glm::vec3(1.0f, 0.0f, 0.0f),     glm::vec3(0.0f, 0.0f, -1.0f)},
            {glm::vec3(0.5f, -0.5f, -0.5f),    glm::vec3(0.0f, 1.0f, 0.0f),     glm::vec3(0.0f, 0.0f, -1.0f)},
            {glm::vec3(0.5f,  0.5f, -0.5f),    glm::vec3(0.0f, 0.0f, 1.0f),     glm::vec3(0.0f, 0.0f, -1.0f)},
            {glm::vec3(-0.5f,  0.5f, -0.5f),   glm::vec3(1.0f, 1.0f, 0.0f),     glm::vec3(0.0f, 0.0f, -1.0f)},
            {glm::vec3(-0.5f, -0.5f,  0.5f),   glm::vec3(1.0f, 0.0f, 0.0f),     glm::vec3(0.0f, 0.0f,  1.0f)},
            {glm::vec3(0.5f, -0.5f,  0.5f),    glm::vec3(0.0f, 1.0f, 0.0f),     glm::vec3(0.0f, 0.0f,  1.0f)},
            {glm::vec3(0.5f,  0.5f,  0.5f),    glm::vec3(0.0f, 0.0f, 1.0f),     glm::vec3(0.0f, 0.0f,  1.0f)},
            {glm::vec3(-0.5f,  0.5f,  0.5f),   glm::vec3(1.0f, 1.0f, 0.0f),     glm::vec3(0.0f, 0.0f,  1.0f)}
        };

        return vertices;
    }

    static inline const std::vector<GLuint> createCubeIndices() {
        return {
            3, 2, 0, 2, 1, 0, // back
            4, 5, 6, 4, 6, 7, // front
            0, 1, 5, 0, 5, 4, // left
            2, 3, 7, 2, 7, 6, // right
            3, 0, 4, 3, 4, 7, // top
            1, 2, 6, 1, 6, 5  // bottom
        };
    }

private:
    glm::mat4 modelMatrix;
    std::vector<Vertex> vertices;
    std::vector<GLuint> indices;
    std::optional<Texture> texture;
    ColorRGB color;
    GLuint VAO, VBO, EBO;

    void setupMesh();
};

#endif // !MESH_H