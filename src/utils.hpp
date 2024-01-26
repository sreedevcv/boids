#pragma once

#define check_for_opengl_error() \
    while (GLenum error = glGetError()) { \
        std::cout << __FILE__ << ":" << __LINE__ << " OpenGL Error: " << error << std::endl; \
    } \


struct BoidConfig {
    float cohesion_radius = 7.0f;
    float alignment_radius = 5.0f;
    float seperation_radius = 5.0f;

    float cohesion_factor = 14.0f;
    float alignment_factor = 6.0f;
    float seperation_factor = 100.0f;

    bool enable_cohesion = true;
    bool enable_seperation = true;
    bool enable_alignment = true;

    float x_boundary = 50.0f;
    float y_boundary = 50.0f;
    float z_boundary = 50.0f;

    float max_speed = 15.0f;
    float min_speed = 5.0f;
    int boid_count = 150;
    float percept_distance = 1.0f;
};

consteval float norm_color(int color) {
    return static_cast<float>(color) / 255.0f;
}