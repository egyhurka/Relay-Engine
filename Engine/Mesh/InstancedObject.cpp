#include "InstancedObject.h"

InstancedObject::InstancedObject(Mesh* mesh) : mesh(mesh) {
	glGenBuffers(1, &instanceVBO);
	glGenBuffers(1, &instanceColorVBO);
    if (instanceVBO == 0) {
        std::cerr << "ERROR::OPENGL::INSTANCE_VBO_NOT_GENERATED" << std::endl;
        return;
    }

    if (instanceColorVBO == 0) {
        std::cerr << "ERROR::OPENGL::INSTANCE_COLOR_VBO_NOT_GENERATED" << std::endl;
        return;
    }

    mesh->isTransparent = true;
}

InstancedObject::~InstancedObject() {
	glDeleteBuffers(1, &instanceVBO);
    glDeleteBuffers(1, &instanceColorVBO);
}

void InstancedObject::addInstancePosition(const glm::vec3& position) {
	instancedPositions.push_back(position);
}

void InstancedObject::addInstanceColor(const ColorRGB color) {
    instancedColors.push_back(color);
}

void InstancedObject::setupInstances() {
    glBindVertexArray(mesh->getVAO());

    glBindBuffer(GL_ARRAY_BUFFER, instanceVBO);
    glBufferData(GL_ARRAY_BUFFER, instancedPositions.size() * sizeof(glm::vec3), instancedPositions.data(), GL_STATIC_DRAW);

    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);
    glVertexAttribDivisor(3, 1);

    glBindBuffer(GL_ARRAY_BUFFER, instanceColorVBO);
    if (isMonochromatic) {
        std::vector<ColorRGB> colors(instancedPositions.size(), instancedColors.at(0));
        glBufferData(GL_ARRAY_BUFFER, colors.size() * sizeof(ColorRGB), colors.data(), GL_STATIC_DRAW);
    }
    else {
        glBufferData(GL_ARRAY_BUFFER, instancedColors.size() * sizeof(ColorRGB), instancedColors.data(), GL_STATIC_DRAW);
    }

    glEnableVertexAttribArray(4);
    glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(ColorRGB), (void*)0);
    glVertexAttribDivisor(4, 1);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    std::cout << "ENGINE::INSTANCES::READY" << std::endl;
}

void InstancedObject::draw(Shader* shader) {
    shader->use();

    glBindVertexArray(mesh->getVAO());

    glDrawElementsInstanced(GL_TRIANGLES, static_cast<GLsizei>(mesh->getVertexCount()), GL_UNSIGNED_INT, 0, instancedPositions.size());
    glBindVertexArray(0);
}