#version 330 core
#extension GL_ARB_separate_shader_objects : enable

layout(location = 0) in vec3 aPos;

out vec3 fragColor;  

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform vec3 uColor;

void main() {
    gl_Position = model * view * projection * vec4(aPos, 1.0);
    fragColor = uColor;
}