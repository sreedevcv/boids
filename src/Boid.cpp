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

    velocity += acceleration;
    clamp_velocity();
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
            alignment_dir += boid->get_velocity();
            count += 1;
        }
    }

    if (count == 0) {
        return impulse;
    }

    alignment_dir /= (float) count;
    if (glm::length(alignment_dir) > 1000.0f) {printf("alignment_dir\n");}
    impulse = alignment_dir * config.alignment_factor;
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

    center_of_mass /= (float) count;
    glm::vec3 desired =  center_of_mass - position;
    desired = glm::normalize(desired);
    impulse = desired * config.cohesion_factor;
    if (glm::length(impulse) > 1000.0f) {printf("cohesion\n");}
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
            avg_distance += glm::normalize(position - boid->get_position()) / (distance);
            count += 1;
        }
    }

    if (count == 0) {
        return impulse;
    }

    avg_distance /= (float) count;
    avg_distance *= config.seperation_factor;
    if (glm::length(avg_distance) > 1000.0f) {printf("avg_distance\n");}
    impulse = avg_distance;
    impulse.z = 0;
    return impulse;
}

void Boid::clamp_velocity() {
    glm::vec3 dir = glm::normalize(velocity);
    float mag = glm::length(velocity);
    float speed = glm::clamp(mag, config.min_speed, config.max_speed);
    velocity = dir * speed;
}

void Boid::draw() {
    glm::mat4 model = glm::mat4(1.0f);
    float angle = std::acos(glm::dot(glm::normalize(velocity), glm::vec3(0.0f, 1.0f, 0.0f)));
    // if (std::isnan(angle)) {printf("hai\n");}
    // float pi = glm::half_pi<float>();
    model = glm::translate(model, position);
    model = glm::scale(model, glm::vec3(1.0f, 2.5f, 1.0f));
    model = glm::rotate(model, angle, glm::vec3(0.0f, 0.0f, 1.0f));
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
