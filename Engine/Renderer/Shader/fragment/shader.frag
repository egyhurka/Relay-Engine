#version 330 core
#extension GL_ARB_separate_shader_objects : enable

in vec4 fragColor;
out vec4 FragColor;

void main() {
    FragColor = fragColor;
}