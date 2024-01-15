#pragma once 

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>


class Shader {
private:
    unsigned int ID;
public:
    Shader() = default;
    ~Shader() = default;

    void compile(const char *vert_shader, const char *frag_shader);
    void use();
    void unload();
};