#version 330 core

layout(location = 0) in vec3 aPos;
layout(location = 3) in vec3 instancePosition;
layout(location = 4) in vec3 instanceColor;

out vec4 fragColor;  

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform vec4 uColor;
uniform bool isInstanced;

void main() {
    fragColor = isInstanced ? vec4(instanceColor, 1.0f) : uColor;

    vec3 finalPosition = isInstanced ? aPos + instancePosition : aPos;
    gl_Position = projection * view * model * vec4(finalPosition, 1.0f);
}