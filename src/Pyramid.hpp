#pragma once

#include <glad/glad.h>
#include <glm/mat4x4.hpp>

#include "Shader.hpp"

class Pyramid {
private:
    unsigned int VAO, VBO;

public:
    Shader basic_shader;

    Pyramid() = default;
    ~Pyramid();

    void load();
    void draw();
};