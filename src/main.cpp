#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

#include "Application.hpp"
#include "Camera.hpp"

void mouse_move_callback(GLFWwindow *window, double x_pos_in, double y_pos_in);
void mouse_scroll_callback(GLFWwindow *window, double x_offset, double y_offset);

int width = 1000;
int height = 800;
Camera camera(width, height);

int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow *window = glfwCreateWindow(width, height, "Boids", nullptr, nullptr);
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
    glfwSetCursorPosCallback(window, mouse_move_callback);
    glfwSetScrollCallback(window, mouse_scroll_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        std::exit(-1);
    }

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


    camera.mouse_data.first_mouse = true;

    ImGui::CreateContext();
    // ImGuiIO& io = ImGui::GetIO();
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    const char* glsl_version = "#version 330";
    ImGui_ImplOpenGL3_Init(glsl_version);

    Application app(window, width, height, camera);
    app.start();
    return 0;
}

void mouse_move_callback(GLFWwindow *window, double x_pos_in, double y_pos_in) {
    float x_pos = static_cast<float>(x_pos_in);
    float y_pos = static_cast<float>(y_pos_in);

    if (camera.mouse_data.first_mouse) {
        camera.mouse_data.last_x = x_pos;
        camera.mouse_data.last_y = y_pos;
        camera.mouse_data.first_mouse = false;
    }
    
    float x_offset = x_pos - camera.mouse_data.last_x;
    float y_offset = camera.mouse_data.last_y - y_pos;

    camera.mouse_data.last_x = x_pos;
    camera.mouse_data.last_y = y_pos;

    camera.process_mouse_movement(x_offset, y_offset);
}

void mouse_scroll_callback(GLFWwindow *window, double x_offset, double y_offset) {
    camera.process_mouse_scroll(static_cast<float>(y_offset));
}


// #include <glad/glad.h>
// #include <GLFW/glfw3.h>
// // #include <stb_image.h>

// #include <glm/glm.hpp>
// #include <glm/gtc/matrix_transform.hpp>
// #include <glm/gtc/type_ptr.hpp>

// // #include <learnopengl/shader_m.h>
// #include "Shader.hpp"

// #include <iostream>

// void framebuffer_size_callback(GLFWwindow* window, int width, int height);
// void processInput(GLFWwindow *window);

// // settings
// const unsigned int SCR_WIDTH = 800;
// const unsigned int SCR_HEIGHT = 600;

// int main()
// {
//     // glfw: initialize and configure
//     // ------------------------------
//     glfwInit();
//     glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//     glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//     glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

// #ifdef __APPLE__
//     glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
// #endif

//     // glfw window creation
//     // --------------------
//     GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
//     if (window == NULL)
//     {
//         std::cout << "Failed to create GLFW window" << std::endl;
//         glfwTerminate();
//         return -1;
//     }
//     glfwMakeContextCurrent(window);
//     glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

//     // glad: load all OpenGL function pointers
//     // ---------------------------------------
//     if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
//     {
//         std::cout << "Failed to initialize GLAD" << std::endl;
//         return -1;
//     }

//     // build and compile our shader zprogram
//     // ------------------------------------
//     // Shader ourShader("6.1.coordinate_systems.vs", "6.1.coordinate_systems.fs");
//     Shader ourShader;
//     ourShader.compile("res/shaders/basic.vert", "res/shaders/basic.frag");
//     // set up vertex data (and buffer(s)) and configure vertex attributes
//     // ------------------------------------------------------------------
//     float vertices[] = {
//         // positions          // texture coords
//          0.5f,  0.5f, 0.0f,
//          0.5f, -0.5f, 0.0f,
//         -0.5f, -0.5f, 0.0f,
//         -0.5f,  0.5f, 0.0f,
//     };
//     unsigned int indices[] = {
//         0, 1, 3, // first triangle
//         1, 2, 3  // second triangle
//     };
//     unsigned int VBO, VAO, EBO;
//     glGenVertexArrays(1, &VAO);
//     glGenBuffers(1, &VBO);
//     glGenBuffers(1, &EBO);

//     glBindVertexArray(VAO);

//     glBindBuffer(GL_ARRAY_BUFFER, VBO);
//     glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

//     glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
//     glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

//     // position attribute
//     glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
//     glEnableVertexAttribArray(0);


//     // render loop
//     // -----------
//     while (!glfwWindowShouldClose(window))
//     {
//         // input
//         // -----
//         processInput(window);

//         // render
//         // ------
//         glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
//         glClear(GL_COLOR_BUFFER_BIT);

//         // bind textures on corresponding texture units
  
//         // activate shader
//         ourShader.use();
      
//         // create transformations
//         glm::mat4 model         = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
//         glm::mat4 view          = glm::mat4(1.0f);
//         glm::mat4 projection    = glm::mat4(1.0f);
//         model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
//         view  = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
//         projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
//         // retrieve the matrix uniform locations
//         // unsigned int modelLoc = glGetUniformLocation(ourShader.ID, "model");
//         // unsigned int viewLoc  = glGetUniformLocation(ourShader.ID, "view");
//         // pass them to the shaders (3 different ways)
//         // glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
//         // glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &view[0][0]);
//         // note: currently we set the projection matrix each frame, but since the projection matrix rarely changes it's often best practice to set it outside the main loop only once.
//         ourShader.set_uniform_matrix("projection", &projection);
//         ourShader.set_uniform_matrix("view", &view);
//         ourShader.set_uniform_matrix("model", &model);

//         // render container
//         glBindVertexArray(VAO);
//         glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

//         // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
//         // -------------------------------------------------------------------------------
//         glfwSwapBuffers(window);
//         glfwPollEvents();
//     }

//     // optional: de-allocate all resources once they've outlived their purpose:
//     // ------------------------------------------------------------------------
//     glDeleteVertexArrays(1, &VAO);
//     glDeleteBuffers(1, &VBO);
//     glDeleteBuffers(1, &EBO);

//     // glfw: terminate, clearing all previously allocated GLFW resources.
//     // ------------------------------------------------------------------
//     glfwTerminate();
//     return 0;
// }

// void processInput(GLFWwindow *window)
// {
//     if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
//         glfwSetWindowShouldClose(window, true);
// }

// // glfw: whenever the window size changed (by OS or user resize) this callback function executes
// // ---------------------------------------------------------------------------------------------
// void framebuffer_size_callback(GLFWwindow* window, int width, int height)
// {
//     // make sure the viewport matches the new window dimensions; note that width and 
//     // height will be significantly larger than specified on retina displays.
//     glViewport(0, 0, width, height);
// }