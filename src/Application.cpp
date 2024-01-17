#include "Application.hpp"

Application::Application() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(width, height, "Boids", nullptr, nullptr);
    if (window == nullptr) {
        std::cout << "Failed to load window\n";
        glfwTerminate();
        std::exit(-1);
    }

    const auto framebuffer_size_callback = [](GLFWwindow *window, int width, int height) {
        glViewport(0, 0, width, height);
    };

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        std::exit(-1);
    }

    glEnable(GL_DEPTH_TEST);

    check_for_opengl_error(__FILE__, __LINE__);

    glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)width/(float)height, 0.1f, 100.0f);
    boid_mesh.load();
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

    glm::mat4 model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
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
