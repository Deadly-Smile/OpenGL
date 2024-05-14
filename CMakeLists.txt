cmake_minimum_required(VERSION 3.0.0)
project(test_opengl_project VERSION 0.1.0)

add_executable(test_opengl_project src/main.cpp)

target_link_libraries(test_opengl_project glfw)