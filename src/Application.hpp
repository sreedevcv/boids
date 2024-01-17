#pragma once 

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>

// #include "Shader.hpp"
// #include "Pyramid.hpp"
#include "Camera.hpp"
#include "Boid.hpp"

class Application {
private:
    int scr_width = 800;
    int scr_height = 600;
    GLFWwindow *window;
    Camera camera;
    Boid *b;

    float movement_speed = 4.0f;
    
    void update(float delta_time);
    void draw();

    

public:
    Application(GLFWwindow *window, const int width, const int height);
    ~Application();

    void start();
    void process_input(float delta_time);
};