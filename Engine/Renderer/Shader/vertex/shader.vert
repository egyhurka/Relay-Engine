#version 330 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 instancePosition;

out vec3 fragColor;  

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform vec3 uColor;
uniform bool isInstanced;

void main() {
    vec3 finalPosition;

    if (isInstanced) {
        finalPosition = aPos + instancePosition;
    } else {
        finalPosition = aPos;
    }

    gl_Position = projection * view * model * vec4(finalPosition, 1.0f);
    fragColor = uColor;
}