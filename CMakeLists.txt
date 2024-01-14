cmake_minimum_required(VERSION 3.27.7)
project(boids VERSION 0.1.0)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})

set(GLFW_USE_WAYLAND, 1)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(deps/glfw)
set_target_properties(glfw PROPERTIES COMPILE_FLAGS "-O3")

add_subdirectory(deps/imgui)
include_directories(deps/imgui-cmake)
include_directories(deps/imgui-cmake/backends)


find_package(OpenGL REQUIRED)

include_directories(include)
include_directories(src)

add_executable(
    boids 
    src/main.cpp
    src/Application.cpp 
    src/glad.c 
)

target_link_libraries(boids glfw ImGui::imgui_core  ${GLFW_LIBRARIES} OpenGL::GL)

# -D GLFW_USE_WAYLAND=1