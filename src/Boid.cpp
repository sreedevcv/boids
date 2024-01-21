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
    position += velocity * delta_time;
}

glm::vec3 Boid::avoid_wall() {
    glm::vec3 impulse = glm::vec3(0.0f);
    glm::vec3 percept_point = position + (glm::normalize(velocity) * percept_point);
    if (abs(percept_point.x) >= config.x_boundary) {
        
    }
    return glm::vec3();
}

glm::vec3 Boid::alignment(std::vector<std::unique_ptr<Boid>> &boids) {
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
    impulse = alignment_dir * config.alignment_factor;
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
    impulse = avg_distance;
    return impulse;
}

void Boid::clamp_velocity() {
    glm::vec3 dir = glm::normalize(velocity);
    float mag = glm::length(velocity);
    float speed = glm::clamp(mag, config.min_speed, config.max_speed);
    velocity = dir * speed;
}

void Boid::draw() {
    glm::vec3 curr_dir = glm::normalize(velocity);
    glm::vec3 local_y_axis = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::vec3 rotation_axis = glm::normalize(glm::cross(local_y_axis, curr_dir));
    float cos_theta = glm::dot(local_y_axis, curr_dir);
    float angle = std::acos(glm::clamp(cos_theta, -1.0f, 1.0f));

    glm::mat4 view = camera.get_view_matrix();
    glm::mat4 model = glm::mat4(1.0f);

    model = glm::translate(model, position);
    model = glm::rotate(model, angle, rotation_axis);
    model = glm::scale(model, glm::vec3(0.8f, 1.5f, 0.8f));
    prev_velocity = velocity;

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

glm::quat Boid::RotationBetweenVectors(glm::vec3 start, glm::vec3 dest){
	start = normalize(start);
	dest = normalize(dest);

	float cosTheta = dot(start, dest);
	glm::vec3 rotationAxis;

	if (cosTheta < -1 + 0.001f){
		// special case when vectors in opposite directions:
		// there is no "ideal" rotation axis
		// So guess one; any will do as long as it's perpendicular to start
		rotationAxis = glm::cross(glm::vec3(0.0f, 0.0f, 1.0f), start);
		if (glm::length2(rotationAxis) < 0.01 ) // bad luck, they were parallel, try again!
			rotationAxis = glm::cross(glm::vec3(1.0f, 0.0f, 0.0f), start);

		rotationAxis = normalize(rotationAxis);
		return glm::angleAxis(glm::radians(180.0f), rotationAxis);
	}

	rotationAxis = glm::cross(start, dest);

	float s = sqrt( (1+cosTheta)*2 );
	float invs = 1 / s;

	return glm::quat(
		s * 0.5f, 
		rotationAxis.x * invs,
		rotationAxis.y * invs,
		rotationAxis.z * invs
	);

}
