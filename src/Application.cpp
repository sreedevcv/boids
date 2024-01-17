#include "Application.hpp"

Application::Application(GLFWwindow *glfw_window, const int width, const int height) :
    window(glfw_window),
    scr_width(width),
    scr_height(height),
    camera(width, height)
{
    glEnable(GL_DEPTH_TEST);

    check_for_opengl_error(__FILE__, __LINE__);

    b = new Boid(camera);
    b->set_position(0.0f, 0.0f, 0.0f);
    b->set_velocity(1.0f, 0.0f, 0.0f);

    check_for_opengl_error(__FILE__, __LINE__);
}

Application::~Application() {
    glfwTerminate();
}

void Application::update(float delta_time) {

    // check_for_opengl_error(__FILE__, __LINE__);
}

void Application::draw() {

    b->draw();
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
