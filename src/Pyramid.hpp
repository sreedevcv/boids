#pragma once

#include <glad/glad.h>
#include <glm/mat4x4.hpp>

#include "Shader.hpp"

class Pyramid {
private:
    unsigned int VAO, VBO, EBO;

public:
    Shader basic_shader;

    Pyramid();
    ~Pyramid();

    void draw();
};