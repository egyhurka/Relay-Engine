#include "InstancedObject.h"

InstancedObject::InstancedObject(Mesh* mesh) : mesh(mesh) {
	glGenBuffers(1, &instanceVBO);
}

InstancedObject::~InstancedObject() {
	glDeleteBuffers(1, &instanceVBO);
}

void InstancedObject::addInstancePosition(const glm::vec3& position) {
	instancedPositions.push_back(position);
}

void InstancedObject::setupInstances() {
    glBindBuffer(GL_ARRAY_BUFFER, instanceVBO);
    glBufferData(GL_ARRAY_BUFFER, instancedPositions.size() * sizeof(glm::vec3), instancedPositions.data(), GL_STATIC_DRAW);

    glBindVertexArray(mesh->getVAO());

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);
    glVertexAttribDivisor(1, 1);

    glBindVertexArray(0);

    std::cout << "ENGINE::INSTANCES::READY" << std::endl;
}

void InstancedObject::draw(Shader* shader) {
    shader->use();
    ColorRGB color = mesh->getColor();
    shader->setColor(color);

    glBindVertexArray(mesh->getVAO());
    glBindBuffer(GL_ARRAY_BUFFER, instanceVBO);

    glDrawElementsInstanced(GL_TRIANGLES, static_cast<GLsizei>(mesh->getVertexCount()), GL_UNSIGNED_INT, 0, instancedPositions.size());
    glBindVertexArray(0);
}