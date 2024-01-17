#include "Application.hpp"

Application::Application(GLFWwindow *glfw_window, const int width, const int height)
    : window(glfw_window),
      scr_width(width),
      scr_height(height) 
{
    glEnable(GL_DEPTH_TEST);

    check_for_opengl_error(__FILE__, __LINE__);

    glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)width/(float)height, 0.1f, 100.0f);
    boid_mesh.basic_shader.use();
    boid_mesh.basic_shader.set_uniform_matrix("projection", &projection);

    check_for_opengl_error(__FILE__, __LINE__);
}

Application::~Application() {
    glfwTerminate();
}

void Application::update() {

    check_for_opengl_error(__FILE__, __LINE__);
}

void Application::draw() {

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));
    glm::mat4 view = glm::lookAt(camera_pos, camera_pos + camera_front, camera_up);

    boid_mesh.basic_shader.use();
    boid_mesh.basic_shader.set_uniform_matrix("view", &view);
    boid_mesh.basic_shader.set_uniform_matrix("model", &model);
    boid_mesh.draw();
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
