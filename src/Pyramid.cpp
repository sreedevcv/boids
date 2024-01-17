#include "Pyramid.hpp"

Pyramid::~Pyramid() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    basic_shader.unload();
}

void Pyramid::load() {
    float vertices[] = {
        // positions        // Colors    
        0.0f,  0.5f,  0.0f, 1.0f, 0.0f, 0.0f, 1.0f,  // Top vertex
        -0.5f, -0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 1.0f,  // Bottom-left vertex
        0.5f, -0.5f,  0.5f, 0.0f, 0.0f, 1.0f, 1.0f,  // Bottom-right vertex
        0.0f, -0.5f, -0.5f, 1.0f, 0.0f, 1.0f, 1.0f,  // Back vertex
    };

    unsigned int indices[] = {
        0, 1, 2,  // Front face
        0, 1, 3,  // Left face
        0, 2, 3,  // Right face
        1, 2, 3   // Bottom face
    };

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), (void*)vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), (void*)indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    basic_shader.compile("res/shaders/basic.vert", "res/shaders/basic.frag");
}

void Pyramid::draw() {
    basic_shader.use();
    glBindVertexArray(VAO);
    // glDrawArrays(GL_TRIANGLES, 0, 12);
    glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0);
}
