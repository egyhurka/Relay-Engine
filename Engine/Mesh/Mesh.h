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
    virtual ~Mesh();

    void rotate(float rotationSpeed, float deltaTime, glm::vec3 axis);
    void scale(float scaleFactor);
    void translate(glm::vec3 position);

    virtual void draw(Shader* shader);

    inline ColorRGB getColor() const { return color; }
    inline const std::optional<Texture> getTexture() const { return texture; };
    inline const glm::mat4& getModelMatrix() const { return modelMatrix; };
    inline const GLuint getVAO() const { return VAO; }
    inline const size_t getVertexCount() const { return indices.size(); }
private:
    glm::mat4 modelMatrix;
    std::vector<Vertex> vertices;
    std::vector<GLuint> indices;
    std::optional<Texture> texture;
    ColorRGB color;
    GLuint VAO, VBO, EBO;
 
    void setupMesh();
};

class CubeMesh : public Mesh {
public:
    CubeMesh(ColorRGB color, std::optional<Texture> Texture);

private:
    inline std::vector<Vertex> createCubeVertices() const {
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

    inline std::vector<GLuint> createCubeIndices() const {
        return {
            3, 2, 0, 2, 1, 0, // back
            4, 5, 6, 4, 6, 7, // front
            0, 1, 5, 0, 5, 4, // left
            2, 3, 7, 2, 7, 6, // right
            3, 0, 4, 3, 4, 7, // top
            1, 2, 6, 1, 6, 5  // bottom
        };
    }
};

#endif // !MESH_H