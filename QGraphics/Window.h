#pragma once

#include "Core.h"
#include "Colour.h"
#include "Camera.h"
static bool initialised = false;

namespace QG
{
	class window
	{
		friend void mouse_callback(GLFWwindow* win, double xPos, double yPos);
	private:
		GLFWwindow* m_window;
		float m_deltaTime = 0;
		float m_lastFrameTime = 0;

		bool camRotate = false;
		bool camPan = false;

		float mouseX;
		float mouseY;
		bool firstMouse = true;

		int m_height;
		int m_width;
		std::string m_title;

		void mouseMove(double xpos, double ypos);

		void(*mouseMoveFunc)(double xpos, double ypos);

	public:
		window(int width, int height, const char* title);
		~window();

		std::unique_ptr<Camera> cam;

		int getHeight() { return m_height; };
		int getWidth() { return m_width; };

		bool running();
		void endFrame();
		void setBackColour(Colour colour);
		void clear();
		float deltaTime() { return m_deltaTime; };

		void addCamera(Camera c);
		void processInput();

		void setMouseMoveFunc(void(*func)(double, double));

		void enableCamRotate();
		void enableCamPan();
		void disableCamRotate();
		void disableCamPan();

		float runtime() { return m_lastFrameTime; };

		void render();
	};


};
