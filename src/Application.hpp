#pragma once 

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>
#include <vector>
#include <memory>
#include <cstdlib>

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
    // Boid *b;
    std::vector<std::unique_ptr<Boid>> boids;
    int boid_count = 20;
    float x_boundary = 20.0f;
    float y_boundary = 20.0f;
    float movement_speed = 7.0f;
    
    void update(float delta_time);
    void draw();    
    void process_input(float delta_time);
    void init_boids();

public:
    Application(GLFWwindow *window, const int width, const int height);
    ~Application();

    void start();
};