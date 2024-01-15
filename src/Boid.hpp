#pragma once

#include <glm/vec3.hpp>

class Boid {
private:
    glm::vec3 position;
    glm::vec3 velocity;
    glm::vec3 acceleration;
    float mass;

public:
    Boid() = default;
    ~Boid() = default;

    void update(float delta_time);
    void set_position(float x, float y, float z);
    void set_velocity(float x, float y, float z);
    void set_acceleration(float x, float y, float z);
};