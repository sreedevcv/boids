#include "Application.hpp"

Application::Application(GLFWwindow *glfw_window, const int width, const int height) :
    window(glfw_window),
    scr_width(width),
    scr_height(height),
    camera(width, height)
{
    glEnable(GL_DEPTH_TEST);

    check_for_opengl_error(__FILE__, __LINE__);

    // Boid boid(camera);
    b = new Boid(camera);

    check_for_opengl_error(__FILE__, __LINE__);
}

Application::~Application() {
    glfwTerminate();
}

void Application::update() {

    // check_for_opengl_error(__FILE__, __LINE__);
}

void Application::draw() {

    b->draw();
}

void Application::start() {
    while (!glfwWindowShouldClose(window)) {

        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
            glfwSetWindowShouldClose(window, true);
        }

        update();

        glClearColor(0.1f, 0.1f, 0.15f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        draw();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    check_for_opengl_error(__FILE__, __LINE__);
}
