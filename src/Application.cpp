#include "Application.hpp"

Application::Application(GLFWwindow *glfw_window, const int width, const int height, Camera& _camera) :
    window(glfw_window),
    scr_width(width),
    scr_height(height),
    camera(_camera)
{
    camera.position.z = 70.0f;
    glClearColor(0.1f, 0.1f, 0.15f, 1.0f);

    init_boids(config);
    check_for_opengl_error();
}

Application::~Application() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();
}

void Application::update(float delta_time) {
    for (auto& boid: boids) {
        boid->update(delta_time, boids);

        glm::vec3& pos = boid->get_position();
        if (std::abs(pos.x) > config.x_boundary) {
            // boid->get_velocity().x *= -1;
            pos.x -= 0.01f * pos.x;
        }
        if (std::abs(pos.y) > config.y_boundary) {
            // boid->get_velocity().y *= -1;
            pos.y -= 0.01f * pos.y;
        }
        if (std::abs(pos.z) > config.z_boundary) {
            // boid->get_velocity().z *= -1;
            pos.z -= 0.01f * pos.z;
        }
    }
}

void Application::draw() {
    for (auto& boid: boids) {
        boid->draw();
    }
}

void Application::start() {
    float prev_time = glfwGetTime();
    bool show_window = true;

    while (!glfwWindowShouldClose(window)) {
        float curr_time = glfwGetTime();
        float delta_time = curr_time - prev_time;
        prev_time = curr_time;

        process_input(delta_time);
        update(delta_time);


        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    // check_for_opengl_error(__FILE__, __LINE__);

        draw();
        draw_ui(show_window, delta_time);
        // draw_cube();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    check_for_opengl_error();
}

void Application::process_input(float delta_time) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        camera.process_movement(Camera::movement::BACKWARD, delta_time);
    }
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        camera.process_movement(Camera::movement::FORWARD, delta_time);
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        camera.process_movement(Camera::movement::LEFT, delta_time);
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        camera.process_movement(Camera::movement::RIGHT, delta_time);
    }
    if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS) {
        camera.mouse_data.captured = true;
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    }
    if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS) {
        camera.mouse_data.captured = false;
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    }

}

void Application::init_boids(BoidConfig& config) {
    boids.clear();

    for (int i = 0; i < config.boid_count; i++) {
        boids.push_back(std::make_unique<Boid>(camera, config));
        
        float p_x = rand() % (int)(2 * config.x_boundary);
        float p_y = rand() % (int)(2 * config.y_boundary);
        float p_z = rand() % (int)(2 * config.z_boundary);
        p_x -= config.x_boundary;
        p_y -= config.y_boundary;
        p_z -= config.z_boundary;
        boids.back()->set_position(p_x, p_y, p_z);

        float v_x = rand() % (int)(2 * config.max_speed);
        float v_y = rand() % (int)(2 * config.max_speed);
        float v_z = rand() % (int)(2 * config.max_speed);
        v_x -= config.max_speed;
        v_y -= config.max_speed;
        v_z -= config.max_speed;
        boids.back()->set_velocity(v_x, v_y, v_z);
        boids.back()->set_acceleration(0.0f, 0.0f, 0.0f);
    }
}

void Application::draw_ui(bool show_window, float delta_time) {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    if (show_window) {
        // ImGui::ShowDemoWindow();

        ImGui::Begin("Controls", &show_window);
        ImGui::Text("FPS: %.2f", 1.0f / delta_time);
        ImGui::Text("Position: %0.1f, %0.1f, %0.1f|Yaw: %0.1f, Pitch: %0.1f", camera.position.x, camera.position.y, camera.position.z, camera.yaw, camera.pitch);

        ImGui::Separator();
        ImGui::Checkbox("Cohesion", &config.enable_cohesion);
        ImGui::DragFloat("Radius##1", &config.cohesion_radius, 0.1f, 0.0f, FLT_MAX);
        ImGui::DragFloat("Factor##1", &config.cohesion_factor, 0.1f, 0.0f, FLT_MAX);
        ImGui::Separator();

        ImGui::Checkbox("Alignment", &config.enable_alignment);
        ImGui::DragFloat("Radius##2", &config.alignment_radius, 0.1f, 0.0f, FLT_MAX);
        ImGui::DragFloat("Factor##2", &config.alignment_factor, 0.1f, 0.0f, FLT_MAX);
        ImGui::Separator();

        ImGui::Checkbox("Seperation", &config.enable_seperation);
        ImGui::DragFloat("Radius##3", &config.seperation_radius, 0.1f, 0.0f, FLT_MAX);
        ImGui::DragFloat("Factor##3", &config.seperation_factor, 0.1f, 0.0f, FLT_MAX);
        ImGui::Separator();

        ImGui::DragFloat("Max Speed", &config.max_speed);
        ImGui::DragFloat("Min Speed", &config.min_speed);
        ImGui::Separator();

        ImGui::DragFloat("X Bounds", &config.x_boundary, 0.1f, 0.0f, FLT_MAX);
        ImGui::DragFloat("Y Bounds", &config.y_boundary, 0.1f, 0.0f, FLT_MAX);
        ImGui::DragFloat("Z Bounds", &config.z_boundary, 0.1f, 0.0f, FLT_MAX);
        ImGui::Separator();

        if (ImGui::Button("Generate")) {
            init_boids(config);
        }
        ImGui::SameLine();
        ImGui::DragInt("Boid Count", &config.boid_count, 1.0f, 0, 1000);

        if (ImGui::Button("Debug")) {
            for (auto& boid: boids) {
                std::cout << boid->get_position().x << " " << boid->get_position().y << " " << boid->get_position().z << " | ";
                std::cout << boid->get_velocity().x << " " << boid->get_velocity().y << " " << boid->get_velocity().z << " | ";
                std::cout << boid->get_acceleration().x << " " << boid->get_acceleration().y << " " << boid->get_acceleration().z << "\n";
            }
        }

        ImGui::End();
    }
    
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void Application::draw_cube() {
    glm::mat4 model = glm::mat4(1.0f);
    glm::vec3 cube_scale = glm::vec3(config.x_boundary, config.y_boundary, config.z_boundary) * 2.0f;
    model = glm::scale(model, cube_scale);
    glm::mat4 view = camera.get_view_matrix();
    glm::mat4 projection = camera.projection;

    cube.basic_shader.use();
    cube.basic_shader.set_uniform_matrix("model", model);
    cube.basic_shader.set_uniform_matrix("view", view);
    cube.basic_shader.set_uniform_matrix("projection", projection);
    cube.draw();
}
