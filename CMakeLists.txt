cmake_minimum_required(VERSION 3.27.7)
project(boids VERSION 0.1.0)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})

# GLFW
set(GLFW_USE_WAYLAND, 1)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(deps/glfw)
include_directories(deps/glfw/include)
set_target_properties(glfw PROPERTIES COMPILE_FLAGS "-O3")

# IMGUI
# add_subdirectory(deps/imgui)
include_directories(deps/imgui)
include_directories(deps/imgui/backends)


add_library(imgui  STATIC
    deps/imgui/imgui.cpp 
    deps/imgui/imgui_demo.cpp 
    deps/imgui/imgui_draw.cpp 
    deps/imgui/imgui_tables.cpp 
    deps/imgui/imgui_widgets.cpp
    deps/imgui/backends/imgui_impl_glfw.cpp
    deps/imgui/backends/imgui_impl_opengl3.cpp 
)

# GLM
set(GLM_BUILD_TESTS OFF)
set(BUILD_SHARED_LIBS ON)
add_subdirectory(deps/glm)
include_directories(deps/glm)

find_package(OpenGL REQUIRED)

include_directories(include)
include_directories(src)

add_executable(
    boids 
    src/main.cpp
    src/Application.cpp 
    src/Shader.cpp 
    src/Boid.cpp 
    src/Pyramid.cpp 
    src/Camera.cpp 
    src/glad.c 
)

target_link_libraries(
    boids 
    glfw 
    # ImGui::imgui_core 
    # ImGui::glfw_opengl3
    imgui 
    ${GLFW_LIBRARIES} 
    OpenGL::GL 
    glm::glm
)

# -D GLFW_USE_WAYLAND=1