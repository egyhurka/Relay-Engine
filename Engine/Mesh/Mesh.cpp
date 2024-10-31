#include "Mesh.h"

Mesh::Mesh(const std::vector<Vertex> vertices, const std::vector<GLuint> indices, const ColorRGB color, const std::optional<Texture> texture)
    : vertices(vertices), indices(indices), color(color), texture(texture), modelMatrix(glm::mat4(1.0f)) {
    setupMesh();
}

Mesh::~Mesh() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}

void Mesh::setupMesh() {
    glGenVertexArrays(1, &VAO);
    if (VAO == 0) {
        std::cerr << "ERROR::OPENGL::VAO_NOT_GENERATED" << std::endl;
        return;
    }

    glGenBuffers(1, &VBO);
    if (VBO == 0) {
        std::cerr << "ERROR::OPENGL::VBO_NOT_GENERATED" << std::endl;
        return;
    }

    glGenBuffers(1, &EBO);
    if (EBO == 0) {
        std::cerr << "ERROR::OPENGL::EBO_NOT_GENERATED" << std::endl;
        return;
    }

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);

    // POSITION ATTRIBUTE
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
    glEnableVertexAttribArray(0);

    // COLOR ATTRIBUTE
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, color));
    glEnableVertexAttribArray(1);

    // NORMAL ATTRIBUTE
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

bool equalv3(glm::vec3 a, glm::vec3 b) {
    return a.x == b.x && a.y == b.y && a.z == b.z;
}

bool Mesh::hasValidVertexColors() {
    for (const Vertex& vert : vertices) {
        if (equalv3(vert.color, glm::vec3(0.0f, 0.0f, 0.0f))) {
            return false;
        }
    }
    return true;
}

void Mesh::rotate(float rotationSpeed, float deltaTime, glm::vec3 axis) {
    modelMatrix = glm::rotate(modelMatrix, glm::radians(rotationSpeed * deltaTime), axis);
}

void Mesh::scale(float scaleFactor) {
    modelMatrix = glm::mat4(1.0f);
    modelMatrix = glm::scale(modelMatrix, glm::vec3(scaleFactor, scaleFactor, scaleFactor));
}

void Mesh::translate(glm::vec3 position) {
    modelMatrix = glm::translate(modelMatrix, position);
}

void Mesh::draw(Shader* shader) {
    shader->setMat4("model", modelMatrix);

    if (!hasValidVertexColors()) {
        shader->setColor(color, 1.0f);
    }

    glBindVertexArray(VAO);

    if (indices.empty()) {
        std::cerr << "ERROR::MESH::DRAW::NO_INDICES_AVAIBLE" << std::endl;
        return;
    }

    if (!isTransparent)
        glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(indices.size()), GL_UNSIGNED_INT, 0);

    glBindVertexArray(0);
}