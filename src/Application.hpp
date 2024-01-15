#pragma once 

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "Shader.hpp"

class Application {
private:
    GLFWwindow *window;
    Shader basic_shader;
    unsigned int triangleVAO;
    
    void update();
    void draw();

public:
    Application();
    ~Application();

    void start();
};