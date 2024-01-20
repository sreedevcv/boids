#pragma once

inline void check_for_opengl_error(const char *file, int line) {
    while (GLenum error = glGetError()) {
        std::cout << file << ":" << line << " OpenGL Error: " << error << std::endl;
    }
}

struct BoidConfig {
    float cohesion_radius = 7.0f;
    float alignment_radius = 6.0f;
    float seperation_radius = 5.0f;

    float cohesion_factor = 2.0f;
    float alignment_factor = 1.5f;
    float seperation_factor = 10.0f;

    bool enable_cohesion = true;
    bool enable_seperation = true;
    bool enable_alignment = true;

    float max_speed = 15.0f;
    float min_speed = 5.0f;
    float x_boundary = 25.0f;
    float y_boundary = 25.0f;
    int boid_count = 250;
};