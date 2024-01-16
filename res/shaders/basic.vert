#version 330 core
layout (location = 0) in vec3 apos;
layout (location = 1) in vec4 aVertColor;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec4 vertColor;

void main() {
    gl_Position = projection * view * model * vec4(apos, 1.0f);
    vertColor = vec4(aVertColor);
}