#version 330 core
layout (location = 0) in vec4 apos;

void main() {
    gl_Position = apos;
}