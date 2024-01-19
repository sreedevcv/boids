#include "Boid.hpp"


Boid::Boid(Camera &main_camera, BoidConfig &boid_config) : 
    camera(main_camera),
     config(boid_config) 
{
    mesh.basic_shader.use();
    mesh.basic_shader.set_uniform_matrix("projection", camera.projection);
    check_for_opengl_error(__FILE__, __LINE__);
}

void Boid::update(float delta_time, std::vector<std::unique_ptr<Boid>>& boids) {
    acceleration = glm::vec3(0.0f);

    if (config.enable_alignment) {
        acceleration += alignment(boids);
    }
    if (config.enable_cohesion) {
        acceleration += cohesion(boids);
    }
    if (config.enable_seperation) {
        acceleration += seperation(boids);
    }

    velocity += acceleration * delta_time;
    velocity = glm::min(velocity, glm::vec3(1.0f) * config.max_speed);
    velocity.z = 0;
    position += velocity * delta_time;
}

glm::vec3 Boid::alignment(std::vector<std::unique_ptr<Boid>>& boids) {
    glm::vec3 impulse = glm::vec3(0.0f);
    glm::vec3 alignment_dir = glm::vec3(0.0f, 0.0f, 0.0f);
    int count = 0;

    for (const auto& boid: boids) {
        if (boid.get() == this) {
            continue;
        }

        float distance = glm::distance(position, boid->get_position());

        if (distance <= config.alignment_radius) {
            alignment_dir += glm::normalize(boid->get_velocity());
            count += 1;
        }
    }

    if (count == 0) {
        return impulse;
    }

    alignment_dir /= count;
    alignment_dir -= velocity;
    alignment_dir = glm::normalize(alignment_dir) * config.max_speed;   // set mag
    if (glm::length(alignment_dir) > 1000.0f) {printf("alignment_dir\n");}
    impulse = glm::min(glm::normalize(alignment_dir) * config.min_speed, alignment_dir);
    impulse.z = 0;
    return impulse;
}

glm::vec3 Boid::cohesion(std::vector<std::unique_ptr<Boid>>& boids) {
    glm::vec3 impulse = glm::vec3(0.0f);
    glm::vec3 center_of_mass = glm::vec3(0.0f, 0.0f, 0.0f);
    int count = 0;

    for (const auto& boid: boids) {
        if (boid.get() == this) {
            continue;
        }

        float distance = glm::distance(position, boid->get_position());

        if (distance <= config.cohesion_radius) {
            center_of_mass += boid->get_position();
            count += 1;
        }
    }

    if (count == 0) {
        return impulse;
    }

    center_of_mass /= count;
    glm::vec3 desired =  center_of_mass - position;
    desired -= velocity;
    desired = glm::normalize(desired) * config.max_speed;   // set mag
    if (glm::length(desired) > 1000.0f) {printf("cohesion\n");}
    impulse = glm::min(glm::normalize(desired) * config.min_speed, desired);

    // if (glm::length(impulse) > 1000.0f) {printf("large ch\n");}
    impulse.z = 0;
    return impulse;
}

glm::vec3 Boid::seperation(std::vector<std::unique_ptr<Boid>>& boids) {
    glm::vec3 impulse = glm::vec3(0.0f);
    glm::vec3 avg_distance = glm::vec3(0.0f, 0.0f, 0.0f);
    int count = 0;

    bool found = false;

    for (const auto& boid: boids) {
        if (boid.get() == this) {
            continue;
        }

        float distance = glm::distance(position, boid->get_position());

        if (distance <= config.seperation_radius) {
            if (distance <= 0.1f) distance = 0.1f;
            avg_distance += (position - boid->get_position()) / (distance);
            count += 1;
        }
    }

    if (count == 0) {
        return impulse;
    }

    avg_distance /= count;
    avg_distance =  avg_distance - velocity;
    avg_distance = glm::normalize(avg_distance) * config.max_speed;   // set mag
    if (glm::length(avg_distance) > 1000.0f) {printf("avg_distance\n");}
    impulse = glm::min(glm::normalize(avg_distance) * config.min_speed, avg_distance);
    // if (glm::length(acceleration) > 1000.0f) {printf("hai\n");}
    impulse.z = 0;
    return impulse;
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
