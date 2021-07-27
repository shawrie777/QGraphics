#include "Window.h"
#include "Asset.h"
#include "Light.h"

namespace QG
{
	void mouse_callback(GLFWwindow* win, double xPos, double yPos);

	void window::processInput()
	{
		for (auto& x:cam->keys)
			if (glfwGetKey(m_window, (int)x.second) == GLFW_PRESS)
			{
				cam->move(x.second, m_deltaTime);				
			}
	}

	void window::setMouseMoveFunc(void(*func)(double, double))
	{
		mouseMoveFunc = func;
	}

	void window::enableCamRotate()
	{
		camRotate = true;
		camPan = false;
		glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	}

	void window::enableCamPan()
	{
		camRotate = false;
		camPan = true;
		glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	}

	void window::disableCamRotate()
	{
		camRotate = false;
		glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);		
	}

	void window::disableCamPan()
	{
		camPan = false;
		glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}

	void window::render()
	{
		glViewport(0, 0, m_width, m_height);
		clear();

		for (auto* x : Assets::assets)
			x->draw();

	}

	void window::mouseMove(double xpos, double ypos)
	{
		if (firstMouse)
		{
			mouseX = (float)xpos;
			mouseY = (float)ypos;
			firstMouse = false;
		}

		float xoffset = (float)xpos - mouseX;
		float yoffset = mouseY - (float)ypos;

		if (camRotate)
		{

			cam->mouseRotate(xoffset, yoffset);
		}
		else if (camPan)
		{
			cam->mouseMove(xoffset, yoffset);
		}
		else
		{
			if (mouseMoveFunc != nullptr)
				mouseMoveFunc(xpos, ypos);
		}
		mouseX = (float)xpos;
		mouseY = (float)ypos;
	}

	window::window(int width, int height, const char* title) : mouseX((float)width / 2.0f), mouseY((float)height / 2.0f)
	{
		m_width = width;
		m_height = height;
		m_title = title;

		if (!initialised)
			initialised = glfwInit();

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		m_window = glfwCreateWindow(width, height, title, NULL, NULL);

		if (m_window == NULL)
		{
			glfwTerminate();
			throw("Failed to create window.");
		}

		glfwSetWindowUserPointer(m_window, this);

		glfwMakeContextCurrent(m_window);
		glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		glEnable(GL_DEPTH_TEST);
		//glEnable(GL_CULL_FACE);
		//glDisable(GL_CULL_FACE);
		glfwSetFramebufferSizeCallback(m_window, framebuffer_size_callback);

		glfwSetKeyCallback(m_window, keyCallback);
		glfwSetMouseButtonCallback(m_window, mouseButtonCallback);

		glfwSetCursorPosCallback(m_window, mouse_callback);

		if (glewInit() != GLEW_OK)
		{
			std::cout << "GLEW failed to initialise." << std::endl;
			std::terminate();
		}

		glEnable(GL_DEBUG_OUTPUT);
		glEnable(GL_TEXTURE_2D);
		glEnable(GL_TEXTURE_3D);
		glDebugMessageCallback(MessageCallback, 0);


		cam = std::make_unique<Camera>(QM::vector<3>(),QM::vector<3>(0.0f,0.0f,-1.0f));

	}

	window::~window()
	{
		glfwTerminate();
	}

	bool window::running()
	{
		return !glfwWindowShouldClose(m_window);
	}

	void window::endFrame()
	{
		float currentTime = (float)glfwGetTime();
		m_deltaTime = currentTime - m_lastFrameTime;
		m_lastFrameTime = currentTime;

		for (auto* x : lighting::pointLights)
			x->fillShadowMap();
		for (auto* x : lighting::spotLights)
			x->fillShadowMap();

		render();

		processInput();
		glfwSwapBuffers(m_window);
		glfwPollEvents();
	}

	void window::setBackColour(Colour colour)
	{
		glClearColor(colour.red(), colour.green(), colour.blue(), colour.alpha());
	}

	void window::clear()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void window::addCamera(Camera c)
	{
		cam.reset(&c);
	}

	void mouse_callback(GLFWwindow* win, double xPos, double yPos)
	{
		window* myWin = (window*)glfwGetWindowUserPointer(win);
		myWin->mouseMove(xPos, yPos);
	}
}