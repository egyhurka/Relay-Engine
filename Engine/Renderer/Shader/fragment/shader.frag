#version 330 core
#extension GL_ARB_separate_shader_objects : enable

in vec3 fragColor;
out vec4 FragColor;

void main() {
    FragColor = vec4(fragColor, 1.0);
}