#pragma once 

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

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
    BoidConfig config;


    std::vector<std::unique_ptr<Boid>> boids;
    float max_speed = 8.0f;
    float player_speed = 7.0f;
    
    void update(float delta_time);
    void draw();    
    void process_input(float delta_time);
    void init_boids(BoidConfig& config);

public:
    Application(GLFWwindow *window, const int width, const int height);
    ~Application();

    void start();
};