#pragma once

inline void check_for_opengl_error(const char *file, int line) {
    while (GLenum error = glGetError()) {
        std::cout << file << ":" << line << " OpenGL Error: " << error << std::endl;
    }
}

struct BoidConfig {
    float cohesion_radius = 5.0f;
    float alignment_radius = 7.0f;
    float seperation_radius = 10.0f;
    float max_speed = 10.0f;
    float min_speed = 1.2f;
    float x_boundary = 25.0f;
    float y_boundary = 25.0f;
    int boid_count = 25;
    bool enable_cohesion = false;
    bool enable_seperation = false;
    bool enable_alignment = false;
};