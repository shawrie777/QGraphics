#pragma once
#include <QMaths.h>
#include <map>

#define GLEW_STATIC
#include "Dependencies/GLEW/glew.h"
#include "Dependencies/GLFW/glfw3.h"
#include "stb_image.h"

#include "ColourDefines.h"
#include "Keycodes.h"

//defines a resizing callback, internal use only
void framebuffer_size_callback(GLFWwindow* window, int width, int height);

//calls key callback from keyFuncs list
//functions can be added to this list using the AddKeyFunc functions
void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

//calls mouse callback from mouseFuncs list
//functions can be added to this list using the AddMouseFunc functions
void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);

//Internal use only
void GLAPIENTRY MessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam);
