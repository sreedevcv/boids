#include "Application.hpp"

Application::Application(GLFWwindow *glfw_window, const int width, const int height) :
    window(glfw_window),
    scr_width(width),
    scr_height(height),
    camera(width, height)
{
    camera.camera_pos.z = 70.0f;

    init_boids(config);
    check_for_opengl_error(__FILE__, __LINE__);
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
            pos.x *= -1;
            // pos.y *= -1;
        }
        if (std::abs(pos.y) > config.y_boundary) {
            // boid->get_velocity().y *= -1;
            // pos.x *= -1;
            pos.y *= -1;
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

        glClearColor(0.1f, 0.1f, 0.15f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        draw();

        if (show_window) {
            // ImGui::ShowDemoWindow();

            ImGui::Begin("Controls", &show_window);
            ImGui::DragFloat("Cohesion Radius", &config.cohesion_radius, 0.1f, 0.0f, FLT_MAX);
            ImGui::DragFloat("Max Speed", &config.max_speed);
            ImGui::DragFloat("Min Speed", &config.min_speed);
            ImGui::DragFloat("X Bounds", &config.x_boundary, 0.1f, 0.0f, FLT_MAX);
            ImGui::DragFloat("Y Bounds", &config.y_boundary, 0.1f, 0.0f, FLT_MAX);
            
            if (ImGui::Button("Generate")) {
                init_boids(config);
            }
            ImGui::SameLine();
            ImGui::DragInt("Boid Count", &boid_count, 1.0f, 0, 1000);

            ImGui::End();
        }
        
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    check_for_opengl_error(__FILE__, __LINE__);
}

void Application::process_input(float delta_time) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        camera.camera_pos.z += player_speed * delta_time;
    }
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        camera.camera_pos.z -= player_speed * delta_time;
    }
}

void Application::init_boids(BoidConfig& config) {
    boids.clear();

    for (int i = 0; i < boid_count; i++) {
        boids.push_back(std::make_unique<Boid>(camera, config));
        
        float p_x = rand() % (int)(2 * config.x_boundary);
        float p_y = rand() % (int)(2 * config.y_boundary);
        p_x -= config.x_boundary;
        p_y -= config.y_boundary;
        boids.back()->set_position(p_x, p_y, 0.0f);

        float v_x = rand() % (int)(2 * max_speed);
        float v_y = rand() % (int)(2 * max_speed);
        v_x -= max_speed;
        v_y -= max_speed;
        boids.back()->set_velocity(v_x, v_y, 0.0f);

        std::cout << p_x << " " << p_y << "\n";
    }
}
