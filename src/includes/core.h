#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

GLFWwindow* create_window(i16 width, i16 height, char* window_name);
