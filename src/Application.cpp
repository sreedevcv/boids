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

    // float vertices[] = {
    //     0.5f, -0.5f, 0.0f, 1.0f,
    //     -0.5f, -0.5f, 0.0f, 1.0f,
    //     0.0f, 0.5f, 0.0f, 1.0f,
    // };

    // float vertices[] = {
    //     // Front face
    //     -0.5f, 0.0f, 0.5f, 1.0f,
    //     0.5f, 0.0f, 0.5f, 1.0f,
    //     0.0f, 0.0f, 0.7f, 1.0f,
    //     // Left face
    //     0.5f, 0.0f, 0.5f, 1.0f,
    //     0.0f, 0.0f, -0.5f, 1.0f,
    //     0.0f, 0.0f, 0.7f, 1.0f,
    //     // Right face
    //     0.5f, 0.0f, -0.5f, 1.0f,
    //     -0.5f, 0.0f, 0.5f, 1.0f,
    //     0.0f, 0.0f, 0.7f, 1.0f,
    //     // Bottom face
    //     0.0f, 0.0f, -0.5f, 1.0f,
    //     0.5f, 0.0f, 0.5f, 1.0f,
    //     -0.5f, 0.0f, 0.5f, 1.0f,
    // };

    // float vertices[] = {
    //     // positions          // texture coords
    //      0.5f,  0.5f, 0.0f,
    //      0.5f, -0.5f, 0.0f,
    //     -0.5f, -0.5f, 0.0f,
    //     -0.5f,  0.5f, 0.0f,
    // };
    // unsigned int indices[] = {
    //     0, 1, 3, // first triangle
    //     1, 2, 3  // second triangle
    // };

    // float vertices[] = {
    //     // positions          // texture coords
    //     -0.5f,  0.0f, 0.5f,
    //     0.5f, 0.0f, 0.5f,
    //     0.5f, 0.0f, -0.5f,
    //     0.0f, 0.5f, 0.0f,
    // };
    // unsigned int indices[] = {
    //     0, 1, 3, // first triangle
    //     1, 2, 3,  // second triangle
    //     2, 0, 3,
    //     2, 1, 0,
    // };
float vertices[] = {
    // positions        // Colors    
    0.0f,  0.5f,  0.0f, 1.0f, 0.0f, 0.0f, 1.0f,  // Top vertex
   -0.5f, -0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 1.0f,  // Bottom-left vertex
    0.5f, -0.5f,  0.5f, 0.0f, 0.0f, 1.0f, 1.0f,  // Bottom-right vertex
    0.0f, -0.5f, -0.5f, 1.0f, 0.0f, 1.0f, 1.0f,  // Back vertex
};

unsigned int indices[] = {
    0, 1, 2,  // Front face
    0, 1, 3,  // Left face
    0, 2, 3,  // Right face
    1, 2, 3   // Bottom face
};

    unsigned int VBO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)width/(float)height, 0.1f, 100.0f);
    basic_shader.compile("res/shaders/basic.vert", "res/shaders/basic.frag");
    // basic_shader.use();
    // basic_shader.set_uniform_matrix("projection", &projection);
    
    check_for_opengl_error(__FILE__, __LINE__);



    // boid_mesh.load();
    // glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)width/(float)height, 0.1f, 100.0f);
    // boid_mesh.basic_shader.use();
    // boid_mesh.basic_shader.set_uniform_matrix("projection", &projection);

}

Application::~Application() {
    // basic_shader.unload();
    glfwTerminate();
}

void Application::update() {
    // glm::mat4 view = glm::lookAt(camera_pos, camera_pos + camera_front, camera_up);
    // glm::mat4 model = glm::mat4(1.0f);
    // model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));

    // // model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
    // // float t = 5.0 * std::sin(glfwGetTime() * 3);

    // // boid_mesh.basic_shader.use();
    // // boid_mesh.basic_shader.set_uniform_matrix("view", &view);
    // // boid_mesh.basic_shader.set_uniform_matrix("model", &model);


    check_for_opengl_error(__FILE__, __LINE__);
}

void Application::draw() {

    glm::mat4 model         = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 view          = glm::mat4(1.0f);
    glm::mat4 projection    = glm::mat4(1.0f);
    model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(0.0f, 1.0f, 0.0f));
    // model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(1.0f, 0.0f, 0.0f));
    model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));
    view  = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
    projection = glm::perspective(glm::radians(45.0f), (float)width / (float)height, 0.1f, 100.0f);


    basic_shader.use();
    basic_shader.set_uniform_matrix("view", &view);
    basic_shader.set_uniform_matrix("model", &model);
    basic_shader.set_uniform_matrix("projection", &projection);
    glBindVertexArray(VAO);
    // glDrawArrays(GL_TRIANGLES, 0, 12);
    glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0);
    // boid_mesh.draw();
    check_for_opengl_error(__FILE__, __LINE__);
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
}
