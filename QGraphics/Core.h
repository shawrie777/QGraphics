#pragma once
#include <QMaths.h>


#define GLEW_STATIC
#include "Dependencies/GLEW/glew.h"
#include "Dependencies/GLFW/glfw3.h"
#include "stb_image.h"

#include "ColourDefines.h"
#include "Keycodes.h"

namespace QG
{
	class spotlight;
	class pointLight;
	class directionalLight;
	class areaLight;

	//std::vector<spotLight*> spotLights;
}


void framebuffer_size_callback(GLFWwindow* window, int width, int height);

void GLAPIENTRY MessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam);
