#pragma once

#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Pyramid.hpp"
#include "Camera.hpp"

class Boid {
private:
    Pyramid mesh;
    Camera& camera;

    glm::vec3 position;
    glm::vec3 velocity;
    glm::vec3 acceleration;
    float mass;

public:
    Boid(Camera &camera);
    ~Boid() = default;

    void update(float delta_time);
    void draw();
    void set_position(float x, float y, float z);
    void set_velocity(float x, float y, float z);
    void set_acceleration(float x, float y, float z);
};