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

		Projection proj = Projection(90,16.0f/9.0f,0.1,1000);

		void updateCameraVectors();

		bool hMove = true;
		bool vMove = false;

		std::map<CameraMovement, keyCode> keys;
	public:
		float movementSpeed = 2.5f;
		float RotateSpeed = 0.1f;
		bool constrainPitch = true;

		Camera(QM::vector<3> position, QM::vector<3> forwards, QM::vector<3> up = QM::vector<3>(0.0f,1.0f,0.0f));
		void addProjection(Projection& P);
		void addProjection(double fovX, double aspect, double near, double far);
		void addProjection(int left, int right, int bottom, int top, int near, int far);

		QM::matrix<4, 4> viewMatrix();
		const QM::matrix<4, 4> projMatrix() const;

		float getPitch() { return Pitch; };
		float getYaw() { return Yaw; };
		float getFOV() { return fov; };

		void setPitch(float pitch) { Pitch = pitch; };
		void setYaw(float yaw) { Yaw = yaw; };
		void setFOV(float FOV) { fov = FOV; };

		void enable_hMove();
		void enable_hMove(keyCode forwards, keyCode backwards, keyCode left, keyCode right);
		void disable_hMove();

		void enable_vMove();
		void enable_vMove(keyCode up, keyCode down);
		void disable_vMove();

		void move(keyCode key, float deltaTime);

		void mouseMove(float xoffset, float yoffset);
		void mouseRotate(float xoffset, float yoffset);
	};

}