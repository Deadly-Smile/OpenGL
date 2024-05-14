cmake_minimum_required(VERSION 3.0.0)
project(test_opengl_project VERSION 0.1.0)

# Manually specify the path to the GLUT library
set(GLUT_LIBRARY "/usr/lib/x86_64-linux-gnu/libglut.so")

add_executable(test_opengl_project src/main.cpp)

# Link GLUT library
target_link_libraries(test_opengl_project ${GLUT_LIBRARY})

# Link OpenGL library
target_link_libraries(test_opengl_project ${CMAKE_DL_LIBS} GL)
