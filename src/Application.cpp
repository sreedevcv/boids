#include "Application.hpp"

Application::Application() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(800, 600, "Boids", nullptr, nullptr);
    if (window == nullptr) {
        std::cout << "Failed to load window\n";
        glfwTerminate();
        std::exit(-1);
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        std::exit(-1);
    }
}

Application::~Application() {
    glfwTerminate();
}

void Application::update() {
}

void Application::draw() {
}

void Application::start() {
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        update();

        glClearColor(0.2f, 0.1f, 0.15f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        draw();

        glfwSwapBuffers(window);
    }
}
