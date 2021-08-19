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
		//create an openGL window with the specified size and title
		window(int width, int height, const char* title);
		~window();

		//the camera currently being used in the window
		std::unique_ptr<Camera> cam;

		int getHeight() { return m_height; };
		int getWidth() { return m_width; };
		
		//check if the window is supposed to be still running
		bool running();
		//complete a frame, drawing all necessary assets, processing input etc..
		void endFrame();
		//set the background colour for the window
		void setBackColour(Colour colour);

		//clear the next frame
		//automatically called in running(), so no need to call manually
		void clear();

		//get the length of time the current frame is taking
		float deltaTime() { return m_deltaTime; };

		//replace the current camera with a new one
		void addCamera(Camera c);

		//process keyboard controls for the camera
		//internal use
		void processInput();

		//set a function to call when the mouse if moved
		//this function should take the mouse coordinates as parameters
		void setMouseMoveFunc(void(*func)(double, double));

		//allow the camera to be rotated using the mouse
		void enableCamRotate();
		//allow the camera to be panned using the mouse
		void enableCamPan();
		//prevent the camera being rotated using the mouse
		void disableCamRotate();
		//prevent the camera being panned using the mouse
		void disableCamPan();

		//check how long the program has been running
		float runtime() { return m_lastFrameTime; };

		//draw all assets in the scene
		//no need to call directly, since it is included in endFrame()
		void render();
	};

	//get a pointer to the current window
	window* getWindow();
};
