#include "Application.hpp"

Application::Application(GLFWwindow *glfw_window, const int width, const int height) :
    window(glfw_window),
    scr_width(width),
    scr_height(height),
    camera(width, height)
{
    glEnable(GL_DEPTH_TEST);

    check_for_opengl_error(__FILE__, __LINE__);

    camera.camera_pos.z = 50.0f;
    init_boids();

    check_for_opengl_error(__FILE__, __LINE__);
}

Application::~Application() {
    glfwTerminate();
}

void Application::update(float delta_time) {
    for (auto& boid: boids) {
        boid->update(delta_time);

        glm::vec3& pos = boid->get_position();
        if (std::abs(pos.x) >= x_boundary) {
            boid->get_velocity().x *= -1;
        }
        if (std::abs(pos.y) >= y_boundary) {
            boid->get_velocity().y *= -1;
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

    while (!glfwWindowShouldClose(window)) {
        float curr_time = glfwGetTime();
        float delta_time = curr_time - prev_time;
        prev_time = curr_time;

        process_input(delta_time);
        update(delta_time);

        glClearColor(0.1f, 0.1f, 0.15f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        draw();

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
        camera.camera_pos.z += movement_speed * delta_time;
    }
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        camera.camera_pos.z -= movement_speed * delta_time;
    }
}

void Application::init_boids() {
    for (int i = 0; i < boid_count; i++) {
        boids.push_back(std::make_unique<Boid>(camera));
        
        float p_x = rand() % (int)(2 * x_boundary);
        float p_y = rand() % (int)(2 * y_boundary);
        p_x -= x_boundary;
        p_y -= y_boundary;
        boids.back()->set_position(p_x, p_y, 0.0f);

        float v_x = rand() % (int)(2 * 5.0f);
        float v_y = rand() % (int)(2 * 5.0f);
        v_x -= 5.0f;
        v_y -= 5.0f;
        boids.back()->set_velocity(v_x, v_y, 0.0f);

        std::cout << p_x << " " << p_y << "\n";
    }
}
