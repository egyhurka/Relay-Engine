#version 330 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aColor;
layout(location = 3) in vec3 instancePosition;
layout(location = 4) in vec3 instanceColor;

out vec4 fragColor;  

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform vec4 uColor;
uniform bool isInstanced;

void main() {
    vec4 color;

    if (aColor != vec3(0.0f, 0.0f, 0.0f)) {
        color = vec4(aColor, 1.0f);
    } else {
        color = uColor;
    }

    fragColor = isInstanced ? vec4(instanceColor, 1.0f) : color;

    vec3 finalPosition = isInstanced ? aPos + instancePosition : aPos;
    gl_Position = projection * view * model * vec4(finalPosition, 1.0f);
}