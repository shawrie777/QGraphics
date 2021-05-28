#include "Camera.h"

namespace QG
{
	void Camera::updateCameraVectors()
	{
		QM::vector<3> front;
		front.set(1, (float)cos((float)QM::rad(Yaw)) * (float)cos(QM::rad(Pitch)));
		front.set(2, (float)sin((float)QM::rad(Pitch)));
		front.set(3, (float)sin((float)QM::rad(Yaw)) * (float)cos(QM::rad(Pitch)));
		m_forwards = front.normalise();
		QM::vector<3> temp(0.0f, 1.0f, 0.0f);
		
		m_right = (m_forwards.cross(temp)).normalise();
		m_up = (m_right.cross(m_forwards)).normalise();
	}
	Camera::Camera(QM::vector<3> position, QM::vector<3> forwards, QM::vector<3> up)
    {
        m_position = position;
        m_forwards = forwards.normalise();
        m_up = up.normalise();
        m_right = (m_forwards.cross(m_up)).normalise();


		keys.emplace(CameraMovement::FORWARD, keyCode::W);
		keys.emplace(CameraMovement::BACKWARD, keyCode::S);
		keys.emplace(CameraMovement::LEFT, keyCode::A);
		keys.emplace(CameraMovement::RIGHT, keyCode::D);
		keys.emplace(CameraMovement::UP, keyCode::SPACE);
		keys.emplace(CameraMovement::DOWN, keyCode::LEFT_CONTROL);
		
    }

	void Camera::addProjection(Projection& P)
	{
			proj = Projection(P);
			updateCameraVectors();
	}
	void Camera::addProjection(double fovX, double aspect, double near, double far)
	{
		proj = Projection(fovX, aspect, near, far);
		updateCameraVectors();
	}

	void Camera::addProjection(int left, int right, int bottom, int top, int near, int far)
	{
			proj = Projection(left, right, bottom, top, near, far);
			updateCameraVectors();
	}

    QM::matrix<4, 4> Camera::viewMatrix()
    {
		QM::vector<3> cameraDirection = -1 * m_forwards;
		cameraDirection = cameraDirection.normalise();

		QM::matrix<4, 4> view1;
		view1.set(1, 1, m_right.get(1));
		view1.set(1, 2, m_right.get(2));
		view1.set(1, 3, m_right.get(3));
		view1.set(2, 1, m_up.get(1));
		view1.set(2, 2, m_up.get(2));
		view1.set(2, 3, m_up.get(3));
		view1.set(3, 1, cameraDirection.get(1));
		view1.set(3, 2, cameraDirection.get(2));
		view1.set(3, 3, cameraDirection.get(3));
		view1.set(4, 4, 1);

		QM::matrix<4, 4> view2;
		view2.set(1, 1, 1);
		view2.set(2, 2, 1);
		view2.set(3, 3, 1);
		view2.set(4, 4, 1);
		view2.set(1, 4, -m_position.get(1));
		view2.set(2, 4, -m_position.get(2));
		view2.set(3, 4, -m_position.get(3));

		QM::matrix<4, 4> view = view1 * view2;
		return view;
    }

	Projection Camera::projMatrix()
	{
		return proj;
	}

	QM::vector<3> Camera::getPosition()
	{
		return m_position;
	}
	void Camera::enable_hMove()
	{
		hMove = true;
	}
	void Camera::enable_hMove(keyCode forwards, keyCode backwards, keyCode left, keyCode right)
	{
		keys[CameraMovement::FORWARD] = forwards;
		keys[CameraMovement::BACKWARD] = backwards;
		keys[CameraMovement::LEFT] = left;
		keys[CameraMovement::RIGHT] = right;
		hMove = true;
	}
	void Camera::disable_hMove()
	{
		hMove = false;
	}
	void Camera::enable_vMove()
	{
		vMove = true;
	}
	void Camera::enable_vMove(keyCode up, keyCode down)
	{
		keys[CameraMovement::UP] = up;
		keys[CameraMovement::DOWN] = down;
		vMove = true;
	}
	void Camera::disable_vMove()
	{
		vMove = false;
	}

	void Camera::mouseRotate(float xoffset, float yoffset)
	{
		xoffset *= RotateSpeed;
		yoffset *= RotateSpeed;

		Yaw += xoffset;
		Pitch += yoffset;

		if (constrainPitch)
		{
			if (Pitch > 89.0f)
				Pitch = 89.0f;
			if (Pitch < -89.0f)
				Pitch = -89.0f;
		}

		updateCameraVectors();
	}

	void Camera::mouseMove(float xoffset, float yoffset)
	{
		QM::vector<3> offset(xoffset, yoffset, 0.0f);
		offset = 0.1f * movementSpeed * offset;
		m_position += offset;

		updateCameraVectors();
	}

	void Camera::move(keyCode key, float deltaTime)
	{
		float distance = movementSpeed * deltaTime;
		if (hMove)
		{
			if (key == keys[CameraMovement::FORWARD])
				m_position += distance * m_forwards;
			if (key == keys[CameraMovement::BACKWARD])
				m_position -= distance * m_forwards;
			if (key == keys[CameraMovement::LEFT])
				m_position -= distance * m_right;
			if (key == keys[CameraMovement::RIGHT])
				m_position += distance * m_right;
		}
		if (vMove)
		{
			if (key == keys[CameraMovement::UP])
				m_position += distance * m_up;
			if (key == keys[CameraMovement::DOWN])
				m_position -= distance * m_up;
		}
	}
}