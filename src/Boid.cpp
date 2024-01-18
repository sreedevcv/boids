#include "Boid.hpp"

Boid::Boid(Camera &main_camera, BoidConfig& boid_config) :
    camera(main_camera),
    config(boid_config) {
    mesh.basic_shader.use();
    mesh.basic_shader.set_uniform_matrix("projection", camera.projection);
    check_for_opengl_error(__FILE__, __LINE__);
}

void Boid::update(float delta_time, std::vector<std::unique_ptr<Boid>>& boids) {
    velocity += acceleration * delta_time;
    position += velocity * delta_time;

    // Cohesion
    glm::vec3 center_of_mass = glm::vec3(0.0f);
    int count = 0;

    for (const auto& boid: boids) {
        if (glm::distance(position, boid->get_position()) <= config.cohesion_radius) {
            center_of_mass += boid->get_position();
            count += 1;
        }
    }

    center_of_mass /= count;
    glm::vec3 desired =  center_of_mass - position;
    desired -= velocity;
    acceleration = glm::normalize(desired) * config.min_speed;   
}


void Boid::alignment() {
    
}

void Boid::draw() {
    glm::mat4 model = glm::mat4(1.0f);
    // model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(0.0f, 1.0f, 0.0f));
    // model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));
    model = glm::translate(model, position);
    glm::mat4 view = glm::lookAt(camera.camera_pos, camera.camera_pos + camera.camera_front, camera.camera_up);

    mesh.basic_shader.use();
    mesh.basic_shader.set_uniform_matrix("view", view);
    mesh.basic_shader.set_uniform_matrix("model", model);
    mesh.draw();
}

void Boid::set_position(float x, float y, float z) {
    position.x = x;
    position.y = y;
    position.z = z;
}

void Boid::set_velocity(float x, float y, float z) {
    velocity.x = x;
    velocity.y = y;
    velocity.z = z;
}

void Boid::set_acceleration(float x, float y, float z) {
    acceleration.x = x;
    acceleration.y = y;
    acceleration.z = z;
}
