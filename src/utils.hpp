#pragma once

inline void check_for_opengl_error(const char *file, int line) {
    while (GLenum error = glGetError()) {
        std::cout << file << ":" << line << " OpenGL Error: " << error << std::endl;
    }
}

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

    float x_boundary = 25.0f;
    float y_boundary = 25.0f;
    float z_boundary = 25.0f;

    float max_speed = 15.0f;
    float min_speed = 5.0f;
    int boid_count = 150;
    float percept_distance = 7.0f;
};

consteval float norm_color(int color) {
    return static_cast<float>(color) / 255.0f;
}