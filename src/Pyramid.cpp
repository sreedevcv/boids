#include "Pyramid.hpp"

Pyramid::~Pyramid() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    basic_shader.unload();
}

void Pyramid::load() {
        float vertices[] = {
        // Front face
        -0.5f, 0.0f, 0.5f, 0.0f,
        0.5f, 0.0f, 0.5f, 0.0f,
        0.0f, 0.0f, 0.7f, 0.0f,
        // Left face
        0.5f, 0.0f, 0.5f, 0.0f,
        0.0f, 0.0f, -0.5f, 0.0f,
        0.0f, 0.0f, 0.7f, 0.0f,
        // Right face
        0.5f, 0.0f, -0.5f, 0.0f,
        -0.5f, 0.0f, 0.5f, 0.0f,
        0.0f, 0.0f, 0.7f, 0.0f,
        // Bottom face
        0.0f, 0.0f, -0.5f, 0.0f,
        0.5f, 0.0f, 0.5f, 0.0f,
        -0.5f, 0.0f, 0.5f, 0.0f,
    };

    glGenBuffers(1, &VBO);
    glGenVertexArrays(1, &VAO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), (void*)vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 4, GL_FLOAT, GL_TRUE, 4 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    basic_shader.compile("res/shaders/basic.vert", "res/shaders/basic.frag");
}

void Pyramid::draw() {
    basic_shader.use();
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 12);
}
