#pragma once 

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/mat4x4.hpp>
#include <glm/gtc/type_ptr.hpp>


class Shader {
private:
    unsigned int ID;
public:
    Shader() = default;
    ~Shader() = default;

    void compile(const char *vert_shader, const char *frag_shader);
    void use();
    void unload();
    void set_uniform_matrix(const char *name, glm::mat4 *value);
};

