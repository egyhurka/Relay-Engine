#include "Mesh.h"

Mesh::Mesh(std::vector<GLfloat> vertices, std::vector<GLuint> indices, ColorRGB color, std::optional<Texture> texture) 
    : vertices(std::move(vertices)), indices(std::move(indices)), color(color), texture(texture), modelMatrix(glm::mat4(1.0f)) {
    setupMesh(this->vertices, this->indices);
}

Mesh::~Mesh() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}

void Mesh::rotate(float rotationSpeed, float deltaTime, glm::vec3 axis) {
    modelMatrix = glm::rotate(modelMatrix, glm::radians(rotationSpeed * deltaTime), axis);
}

void Mesh::draw() {
    glBindVertexArray(VAO);

    if (this->indices.empty()) {
        std::cerr << "ERROR::MESH::DRAW::NO_INDICES_AVAIBLE" << std::endl;
        return;
    }

    glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(this->indices.size()), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void Mesh::setupMesh(std::vector<GLfloat> vertices, std::vector<GLuint> indices) {
    glGenVertexArrays(1, &VAO);
    if (VAO == 0) {
        std::cerr << "ERROR::OPENGL::VAO_NOT_GENERATED" << std::endl;
    }

    glGenBuffers(1, &VBO);
    if (VBO == 0) {
        std::cerr << "ERROR::OPENGL::VBO_NOT_GENERATED" << std::endl;
    }

    glGenBuffers(1, &EBO);
    if (EBO == 0) {
        std::cerr << "ERROR::OPENGL::EBO_NOT_GENERATED" << std::endl;
    }

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Mesh::translate(glm::vec3 position) {
    modelMatrix = glm::translate(modelMatrix, position);
}

CubeMesh::CubeMesh(ColorRGB color, std::optional<Texture> Texture) : Mesh(createCubeVertices(), createCubeIndices(), color, std::nullopt) {}