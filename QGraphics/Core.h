#pragma once
#include <QMaths.h>
#include <map>

#define GLEW_STATIC
#include "Dependencies/GLEW/glew.h"
#include "Dependencies/GLFW/glfw3.h"
#include "stb_image.h"

#include "ColourDefines.h"
#include "Keycodes.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);

void GLAPIENTRY MessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam);
