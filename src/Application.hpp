#pragma once 

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

class Application {
private:
    GLFWwindow *window;
    
    void update();
    void draw();
    
public:
    Application();
    ~Application();

    void start();
};