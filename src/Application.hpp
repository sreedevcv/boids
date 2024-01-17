#pragma once 

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>

// #include "Shader.hpp"
#include "Pyramid.hpp"

class Application {
private:
    int scr_width = 800;
    int scr_height = 600;
    GLFWwindow *window;
    Pyramid boid_mesh;

    glm::vec3 camera_pos = glm::vec3(0.0f, 0.0f, 10.0f);
    glm::vec3 camera_front = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 camera_up = glm::vec3(0.0f, 1.0f, 0.0f);
    
    void update();
    void draw();

    inline void check_for_opengl_error(const char *file, int line) {
        while (GLenum error = glGetError()) {
            std::cout << file << ":" << line << " OpenGL Error: " << error << std::endl;
        }
    }

public:
    Application(GLFWwindow *window, const int width, const int height);
    ~Application();

    void start();
};