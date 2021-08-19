#pragma once

#include "Core.h"
#include "Projections.h"
#include <map>
namespace QG
{
	enum class CameraMovement {
		FORWARD,
		BACKWARD,
		LEFT,
		RIGHT,
		UP,
		DOWN
	};

	class Camera
	{
		friend class window;
	private:
		QM::vector<3> m_position;
		QM::vector<3> m_forwards;
		QM::vector<3> m_right;
		QM::vector<3> m_up;

		float Pitch = 0.0f;
		float Yaw = -90.0f;
		float fov = 90.0f;

		Projection proj = Projection(90,16.0f/9.0f,0.1,200);

		void updateCameraVectors();

		bool hMove = true;
		bool vMove = false;

		std::map<CameraMovement, keyCode> keys;
	public:
		float movementSpeed = 5.0f;
		float RotateSpeed = 0.05f;
		bool constrainPitch = true;

		//create a camera at the given position and orientation
		//the up vector aligns with the worlds up direction by default
		//also creates an associated perspective projection matrrix:
		//fov=90, aspect ratio=16/9, near-plane=0.1, far-plane=200
		//this can be replaced using the addProjection functions
		//also creates default camera controls for movement in each direction
		Camera(QM::vector<3> position, QM::vector<3> forwards, QM::vector<3> up = QM::vector<3>(0.0f,1.0f,0.0f));
		//binds a projection matrix to the camera
		void addProjection(Projection& P);
		//creates a perspective projection matrix and attaches it to the camera
		void addProjection(double fovX, double aspect, double near, double far);
		//creates an orthographic projection matrix and attaches it to the camera
		void addProjection(int left, int right, int bottom, int top, int near, int far);

		//gets the view matrix for this camera
		QM::matrix<4, 4> viewMatrix();
		//gets the projection matrix for this camera
		Projection projMatrix();

		//set the camera's position in the world
		void setPosition(QM::vector<3> pos);
		//get the camera's position in the world
		QM::vector<3> getPosition();

		//get current forward vector
		QM::vector<3> getForward() const;
		//get current up vector
		QM::vector<3> getUp() const;
		//get current right vector
		QM::vector<3> getRight() const;

		//get the distance to the near plane from the projection matrix
		float getNear() { return (float)proj.getNear(); };

		//get the current pitch (up/down angle), 0 is horizontal
		float getPitch() { return Pitch; };
		//get current yaw (left/right angle), -90 is default, looking down z-axis
		float getYaw() { return Yaw; };
		//get current field of view (horizontally)
		float getFOV() { return fov; };

		//set the pitch (up/down angle), 0 is horizontal
		void setPitch(float pitch);
		//set yaw (left/right angle), -90 is default, looking down z-axis
		void setYaw(float yaw);
		//set field of view (horizontally)
		void setFOV(float FOV);

		//allows the camera to move horizontally
		void enable_hMove();
		//allows the camera to move horizontally
		//also allows assigning new keys to navigate with
		void enable_hMove(keyCode forwards, keyCode backwards, keyCode left, keyCode right);
		//prevent the camera moving horizontally
		void disable_hMove();

		//allows the camera to move vertically
		void enable_vMove();
		//allows the camera to move vertically
		//also allows assigning new keys to navigate with
		void enable_vMove(keyCode up, keyCode down);
		//prevent the camera moving vertically
		void disable_vMove();

		//moves the camera at a steady rate, using keyboard
		//internal use only
		void move(keyCode key, float deltaTime);

		//pans the camera using the mouse
		//internal use only
		void mouseMove(float xoffset, float yoffset);

		//rotates the camera using the mouse
		//internal use only
		void mouseRotate(float xoffset, float yoffset);

		//checks if the camera is using perspective or orthographic projection
		camType getProjType() const { return proj.getType(); };

	};

}