#pragma once

#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>

#include <vector>
#include <memory>

#include "Tetrahedron.hpp"
#include "Camera.hpp"

class Boid {
private:
    Tetrahedron mesh;
    Camera& camera;
    BoidConfig& config;

    glm::vec3 position;
    glm::vec3 velocity;
    glm::vec3 acceleration;
    float prev_angle = 0;
    // float mass;

    glm::vec3 avoid_wall();
    glm::vec3 alignment(std::vector<std::unique_ptr<Boid>>& boids);
    glm::vec3 cohesion(std::vector<std::unique_ptr<Boid>>& boids);
    glm::vec3 seperation(std::vector<std::unique_ptr<Boid>>& boids);

    void clamp_velocity();
public:
    glm::vec3 prev_velocity;
    Boid(Camera &camera, BoidConfig& boid_config);
    ~Boid() = default;

    void update(float delta_time, std::vector<std::unique_ptr<Boid>>& boids);
    void draw();
    void set_position(float x, float y, float z);
    void set_velocity(float x, float y, float z);
    void set_acceleration(float x, float y, float z);

    inline glm::vec3& get_position() {
        return position;
    }

    inline glm::vec3& get_velocity() {
        return velocity;
    }

    inline glm::vec3& get_acceleration() {
        return acceleration;
    }    
};